/*
 * buttons.h
 *
 *  Created on: Feb 4, 2025
 *      Author: pholo
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "main.h"

//External global variables
extern uint8_t SELECT;
extern uint8_t BACK;
extern uint8_t UP;
extern uint8_t DOWN;
extern uint8_t BLUETOOTH;
extern uint8_t SPEED_BUTTON;
extern uint8_t STEER_BUTTON;

//Functions
void set_SELECT();
void set_BACK();
void set_UP();
void set_DOWN();
void set_BLUETOOTH();
void set_SPEED_BUTTON();
void set_STEER_BUTTON();

// Initializer
void buttons_Init();

//Polling buttons
void buttons_poll();


#endif /* INC_BUTTONS_H_ */
