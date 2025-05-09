/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "switches.h"
#include "buttons.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
//void SysTick_CallBack(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Speed_VRx_Pin GPIO_PIN_0
#define Speed_VRx_GPIO_Port GPIOA
#define Speed_VRy_Pin GPIO_PIN_1
#define Speed_VRy_GPIO_Port GPIOA
#define Steer_VRx_Pin GPIO_PIN_2
#define Steer_VRx_GPIO_Port GPIOA
#define Steer_VRy_Pin GPIO_PIN_3
#define Steer_VRy_GPIO_Port GPIOA
#define Speed_Pot_Pin GPIO_PIN_4
#define Speed_Pot_GPIO_Port GPIOA
#define Steer_Pot_Pin GPIO_PIN_5
#define Steer_Pot_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_7
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_0
#define SW2_GPIO_Port GPIOB
#define SW3_Pin GPIO_PIN_1
#define SW3_GPIO_Port GPIOB
#define Steer_SW2_Pin GPIO_PIN_12
#define Steer_SW2_GPIO_Port GPIOB
#define Steer_SW1_Pin GPIO_PIN_13
#define Steer_SW1_GPIO_Port GPIOB
#define Speed_SW2_Pin GPIO_PIN_14
#define Speed_SW2_GPIO_Port GPIOB
#define Speed_SW1_Pin GPIO_PIN_15
#define Speed_SW1_GPIO_Port GPIOB
#define A_Select_Pin GPIO_PIN_8
#define A_Select_GPIO_Port GPIOA
#define B_Back_Pin GPIO_PIN_9
#define B_Back_GPIO_Port GPIOA
#define C_Up_Pin GPIO_PIN_10
#define C_Up_GPIO_Port GPIOA
#define D_Down_Pin GPIO_PIN_11
#define D_Down_GPIO_Port GPIOA
#define E_backlight_toggle_Pin GPIO_PIN_12
#define E_backlight_toggle_GPIO_Port GPIOA
#define Steers_Button_Pin GPIO_PIN_15
#define Steers_Button_GPIO_Port GPIOA
#define Speed_Button_Pin GPIO_PIN_3
#define Speed_Button_GPIO_Port GPIOB
#define BT_EN_OUT_Pin GPIO_PIN_4
#define BT_EN_OUT_GPIO_Port GPIOB
#define BT_STATE_IN_Pin GPIO_PIN_5
#define BT_STATE_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
