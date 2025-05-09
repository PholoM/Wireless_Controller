/*
 * buttons.c
 *
 *  Created on: Feb 4, 2025
 *      Author: pholo
 */


#include "buttons.h"

uint8_t SELECT;
uint8_t BACK;
uint8_t UP;
uint8_t DOWN;
uint8_t BLUETOOTH;
uint8_t SPEED_BUTTON;
uint8_t STEER_BUTTON;

// For OK button
void set_SELECT() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)) SELECT =1;
	else SELECT = 0;
}

void set_BACK() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)) BACK =1;
	else BACK = 0;
}

void set_UP() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) UP =1;
	else UP = 0;
}

void set_DOWN() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)) DOWN =1;
	else DOWN = 0;
}

void set_BLUETOOTH() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12)) BLUETOOTH =1;
	else BLUETOOTH = 0;
}

void set_SPEED_BUTTON() {
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)) SPEED_BUTTON =0;
	else SPEED_BUTTON = 1;
}

void set_STEER_BUTTON() {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15)) STEER_BUTTON =0;
	else STEER_BUTTON = 1;
}

void buttons_Init(){
	set_SELECT();
	set_BACK();
	set_UP();
	set_DOWN();
	set_BLUETOOTH();
	set_SPEED_BUTTON();
	set_STEER_BUTTON();
}

void buttons_poll() {
	set_SELECT();
	set_BACK();
	set_UP();
	set_DOWN();
	set_BLUETOOTH();
	set_SPEED_BUTTON();
	set_STEER_BUTTON();
}
