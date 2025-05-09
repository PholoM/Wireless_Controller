#ifndef SWITCHES_H_

#define SWITCHES_H_

#include "main.h"

// External global variables
extern uint8_t steeringMode;
extern uint8_t driveMode;
extern uint8_t screenLight;
extern uint8_t SW2_variable;
extern uint8_t SW1_variable;

// Functions
void set_steeringMode();
void set_driveMode();
void set_screenLight();
void set_SW2_variable();
void set_SW1_variable();

// Initializer
void switches_Init();

// Polling switches
void switches_poll();

#endif
