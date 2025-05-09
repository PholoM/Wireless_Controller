/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "../../ECUAL/I2C_LCD/I2C_LCD.h"
#include "switches.h"
#include "buttons.h"
#include "../../ECUAL/JOYSTICK/JOYSTICK.h"

#define MyI2C_LCD I2C_LCD_1
#define Joystick1 0
#define Joystick2 1
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

struct Packet{


	uint8_t isValid;
	uint32_t Header;
	uint32_t Headlights;
	uint32_t DriveMode;
	uint32_t WheelAngle;
	uint32_t WheelSpeed;
	uint32_t Tail;
	uint8_t Sent_received;



};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE BEGIN PV */

//uint8_t Buffer[25] = {0};
//uint8_t Space[] = " - ";
//uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
//uint8_t EndMSG[] = "Done! \r\n\r\n";

// Word to transmit
uint8_t Package[80] = {'\0'};

//ADC Values
uint32_t ADC_results[6] = {2048};




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

//Function to update the package details
static void sendPackage(void);

// Function to read switches


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct Packet txPacket;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_ADCEx_Calibration_Start(&hadc1);

  uint8_t previousMode = 0;

  txPacket.Header = 1100;
  txPacket.Tail = 0011;

  //LCD setup
  I2C_LCD_Init(MyI2C_LCD);
  I2C_LCD_Clear(MyI2C_LCD);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


/*
  	I2C_LCD_Init(MyI2C_LCD);
	I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
	I2C_LCD_WriteString(MyI2C_LCD, "starting");
	I2C_LCD_SetCursor(MyI2C_LCD, 0, 1);
	I2C_LCD_WriteString(MyI2C_LCD, "++++++++");
	HAL_Delay(500);


	  uint8_t MSG[35] = {'\0'};
	  */


  //HAL_ADC_Start_DMA(&hadc1, ADC_results, 6);
  while (1)
  {

	  //0. poll switches
	  switches_Init();
	  buttons_Init();

	  // 1. If DriveMode = Idle, ADC DMA must stop. (SW50)
	  txPacket.DriveMode = driveMode;
	  if (txPacket.DriveMode == 0) {
		  HAL_ADC_Stop_DMA(&hadc1);
		  txPacket.WheelAngle = 2048;
		  txPacket.WheelSpeed = 2048;
		  previousMode = 0;
	  }

	  //else if ((txPacket.DriveMode != 0) && (previousMode = 0)) {
		  //HAL_ADC_Start_DMA(&hadc1, ADC_results, 6);
		  //previousMode = 1;
	  //}
	  else {
		  // DMA is already running
	  HAL_ADC_Start_DMA(&hadc1, ADC_results, 6);
	  		  previousMode = 1;
	  }



	  //2. if the screenLight switch is ON (SW3)
	  if (screenLight){
		  I2C_LCD_Backlight(MyI2C_LCD);
	  }
	  else I2C_LCD_NoBacklight(MyI2C_LCD);


	  //3. SW2 to be used for Headlights
	  txPacket.Headlights = SW2_variable;

	  /*
	  //I2C_LCD_SetCursor(MyI2C_LCD, 2, 0);
	  if (SW2_variable){
		  //I2C_LCD_WriteString(MyI2C_LCD, "1");
		  txPacket.Headlights = SW2_variable;
	  }
	  else {
		  //I2C_LCD_WriteString(MyI2C_LCD, "0");
		  txPacket.Headlights = SW2_variable;

	  }
	  */


	  //4. Write a function here for SW1



	  //5. SW40 controls which analog channel to use
	  if(txPacket.DriveMode !=0) {
		  switch(steeringMode)
		  {
			  case 0:
				  txPacket.WheelAngle = ADC_results[0];
				  txPacket.WheelSpeed = ADC_results[3];
				  break;

			  case 1:
				  //txPacket.WheelAngle = 1013;
				  //txPacket.WheelSpeed = 1014;
				  txPacket.WheelAngle = ADC_results[4];
				  txPacket.WheelSpeed = ADC_results[5];

				  break;

				  // Add case 2 here for the IMU
			  case 2:
				  txPacket.WheelAngle = 1015;
				  txPacket.WheelSpeed = 1016;
				  //txPacket.WheelAngle = ADC_results[0];
				  //txPacket.WheelSpeed = ADC_results[1];

				  break;
		  }
	  }


	  sendPackage();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  //ReadSwitches();

/*

	  //Printing switch states();
	  I2C_LCD_Clear(MyI2C_LCD);
	  I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);


	 I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
	 if (steeringMode >1) I2C_LCD_WriteString(MyI2C_LCD, "2");
	 else if (steeringMode <1) I2C_LCD_WriteString(MyI2C_LCD, "0");
	 else I2C_LCD_WriteString(MyI2C_LCD, "1");

	 I2C_LCD_SetCursor(MyI2C_LCD, 1, 0);
	 if (SW1_variable)(I2C_LCD_WriteString(MyI2C_LCD, "1"));
	 else I2C_LCD_WriteString(MyI2C_LCD, "0");



	 I2C_LCD_SetCursor(MyI2C_LCD, 3, 0);
	 if (screenLight)(I2C_LCD_WriteString(MyI2C_LCD, "1"));
	 else I2C_LCD_WriteString(MyI2C_LCD, "0");

	 I2C_LCD_SetCursor(MyI2C_LCD, 4, 0);
     if (driveMode >1) I2C_LCD_WriteString(MyI2C_LCD, "2");
     else if (driveMode <1) I2C_LCD_WriteString(MyI2C_LCD, "0");
     else I2C_LCD_WriteString(MyI2C_LCD, "1");
*/
// printing button states

	I2C_LCD_SetCursor(MyI2C_LCD, 0, 1);
	 if (SELECT ) I2C_LCD_WriteString(MyI2C_LCD, "1");
	 else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 1, 1);
	if (BACK)(I2C_LCD_WriteString(MyI2C_LCD, "1"));
	else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 2, 1);
	if (UP)(I2C_LCD_WriteString(MyI2C_LCD, "1"));
	else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 3, 1);
	if (DOWN)(I2C_LCD_WriteString(MyI2C_LCD, "1"));
	else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 4, 1);
	if (BLUETOOTH) I2C_LCD_WriteString(MyI2C_LCD, "1");
	else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 5, 1);
	if (SPEED_BUTTON) I2C_LCD_WriteString(MyI2C_LCD, "1");
	else I2C_LCD_WriteString(MyI2C_LCD, "0");

	I2C_LCD_SetCursor(MyI2C_LCD, 6, 1);
	if (STEER_BUTTON) I2C_LCD_WriteString(MyI2C_LCD, "1");
	else I2C_LCD_WriteString(MyI2C_LCD, "0");
/*
	//Print reading to screen
	I2C_LCD_SetCursor(MyI2C_LCD, 8, 0);
	JoyStick_Read(Joystick1, Joystick1_XY);
	I2C_LCD_WriteString(MyI2C_LCD, (char*)&Joystick1_XY[0]);

	I2C_LCD_SetCursor(MyI2C_LCD, 8, 1);
	JoyStick_Read(Joystick2, Joystick2_XY);
	I2C_LCD_WriteString(MyI2C_LCD, (char*)(intptr_t)Joystick2_XY[1]);



	sprintf(MSG, "Joystick1: = %hd \r\n", (uint8_t)Joystick1_XY[0]);
	HAL_UART_Transmit(&huart3, MSG, sizeof(MSG), 100);
	sprintf(MSG, "Joystick2: = %hd \r\n", (uint8_t)Joystick2_XY[1]);
	HAL_UART_Transmit(&huart3, MSG, sizeof(MSG), 100);
*/
	HAL_Delay(200);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 6;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BT_EN_OUT_GPIO_Port, BT_EN_OUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW1_Pin E_backlight_toggle_Pin */
  GPIO_InitStruct.Pin = SW1_Pin|E_backlight_toggle_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin SW3_Pin Steer_SW2_Pin Steer_SW1_Pin
                           Speed_SW2_Pin Speed_SW1_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|SW3_Pin|Steer_SW2_Pin|Steer_SW1_Pin
                          |Speed_SW2_Pin|Speed_SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Select_Pin B_Back_Pin C_Up_Pin D_Down_Pin
                           Steers_Button_Pin */
  GPIO_InitStruct.Pin = A_Select_Pin|B_Back_Pin|C_Up_Pin|D_Down_Pin
                          |Steers_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Speed_Button_Pin */
  GPIO_InitStruct.Pin = Speed_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Speed_Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BT_EN_OUT_Pin */
  GPIO_InitStruct.Pin = BT_EN_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BT_EN_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BT_STATE_IN_Pin */
  GPIO_InitStruct.Pin = BT_STATE_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BT_STATE_IN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	txPacket.isValid = 1;
	txPacket.Sent_received = 0;
	//sprintf((char*)Package, "ADC %u\r\n",(unsigned int)ADC_results);
	/*
	sprintf((char*)Package, "ADC %04u %04u %04u %04u %04u %04u\n",
			(unsigned int)ADC_results[0],
			(unsigned int)ADC_results[1],
			(unsigned int)ADC_results[2],
			(unsigned int)ADC_results[3],
			(unsigned int)ADC_results[4],
			(unsigned int)ADC_results[5]);
			*/
	//HAL_UART_Transmit_DMA(&huart3, Package, sizeof(Package));

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	txPacket.isValid = 0;
	txPacket.Sent_received = 1;
}

void sendPackage(void){
	sprintf((char*)Package, "%04u %04u %04u %04u %04u %04u\n",
			(unsigned int)txPacket.Header,
			(unsigned int)txPacket.Headlights,
			(unsigned int)txPacket.DriveMode,
			(unsigned int)txPacket.WheelAngle,
			(unsigned int)txPacket.WheelSpeed,
			(unsigned int)txPacket.Tail);
	//HAL_UART_Transmit_DMA(&huart3, Package, sizeof(Package));
	HAL_UART_Transmit_DMA(&huart1, Package, sizeof(Package));
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
