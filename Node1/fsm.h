/*
 * menu.h
 *
 * Created: 27.09.2017 13:04:08
 *  Author: mariuesk
 */ 
#ifndef fsm_H_
#define fsm_H_

#include "OLED.h"
#include "Utilities.h"
#include <avr/io.h>
#include "joystick.h"
#include "Usart_Driver.h"
#include "Memory.h"
#include "ADC.h"
#include "CAN.h"
#include "CAN_joystick.h"
#include "Pong.h"
#include "Menus.h"
static uint8_t currentState;

typedef enum tag_fsm_state {
	STATE_MAIN_MENU = 0,
	GAME = 1,
	SNEK = 2,
	THANKS_TO = 3,
} fsm_state;

#define JOY 0
#define SLIDER 1

void fsm_evInit();
void fsm_evMainMenu();
void fsm_evPong();
void fsm_evSnek();
void fsm_evThanksTo();
void fsm_evMenu4();
int fsm_evMenuNavigate();

int fsm_getCurrentState();
void fsm_evReturn(void);
#endif 