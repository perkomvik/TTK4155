/*
 * menu.h
 *
 * Created: 27.09.2017 13:04:08
 *  Author: mariuesk
 */ 
#ifndef fsm_H_
#define fsm_H_
#include <avr/io.h>
#include "utilities.h"
#include "USART.h"
#include "memory.h"
#include "ADC.h"
#include "joystick.h"
#include "OLED.h"
#include "CAN.h"
#include "CAN_joystick.h"
#include "pong.h"
#include "menus.h"




typedef enum tag_fsm_state {
	STATE_MAIN_MENU = 0,
	STATE_PONG = 1,
	STATE_SNEK = 2,
	STATE_THANKS_TO = 3
} fsm_state;

typedef enum tag_game_mode{
	JOY = 0,
	SLIDER = 1
}game_mode;

static uint8_t currentState;

void fsm_evInit(void);
void fsm_evMainMenu(void);
void fsm_evPong(void);
void fsm_evSnek(void);
void fsm_evThanksTo(void);
void fsm_evMenu4(void);
OLED_line fsm_menuNavigate(OLED_line max_line);

fsm_state fsm_getCurrentState(void);
void fsm_evReturn(void);
#endif 