/*
 * switches.c
 *
 *  Created on: Jan 16, 2025
 *      Author: pholo
 */

#include "switches.h"

uint8_t steeringMode;
uint8_t driveMode;
uint8_t screenLight;
uint8_t SW2_variable;
uint8_t SW1_variable;

//For STEERING SWITCH
void set_steeringMode() {
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) steeringMode =1;
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)) steeringMode = 2;
	else steeringMode = 0;
}

//FOR SPEED SPEECH
void set_driveMode() {
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) driveMode =1;
	else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)) driveMode = 2;
	else driveMode = 0;
}

//FOR SW3
void set_screenLight() {

	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1))screenLight = 1;
	else screenLight = 0;
}

//FOR SW2
void set_SW2_variable() {

	// to be updated.
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))SW2_variable = 1;
	else SW2_variable = 0;
}

//FOR SW1
void set_SW1_variable() {

	//To be updated
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7))SW1_variable = 1;
	else SW1_variable = 0;
}

void switches_Init() {
	set_steeringMode();
	set_driveMode();
	set_screenLight();
	set_SW2_variable();
	set_SW1_variable();
}

void switches_poll() {
	set_steeringMode();
	set_driveMode();
	set_screenLight();
	set_SW2_variable();
	set_SW1_variable();
}
