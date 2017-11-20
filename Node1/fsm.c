/*
 * menu.c
 *
 * Created: 27.09.2017 13:03:58
 *  Author: mariuesk
 */ 


#include "fsm.h"

fsm_state fsm_getCurrentState(void){
	return currentState;
}


void fsm_evInit(void){
	USART_Init();
	init_memory();
	_delay_us(100); //NEEDED?
	//SRAM_test();
	JOY_init();
	OLED_init();
	CAN_init(MODE_NORMAL);
	fsm_evMainMenu();
}

void fsm_evMainMenu(void){
	OLED_clear();
	OLED_store_menu(MAIN_MENU);
	OLED_refresh();
	currentState = STATE_MAIN_MENU;
}

void fsm_evPong(void){
	OLED_clear();
	OLED_store_menu(PONG_MENU);
	OLED_refresh();
	currentState = STATE_PONG;
}

void fsm_evSnek(void){
	OLED_clear();
	OLED_store_menu(SNEK_MENU);
	OLED_refresh();
	currentState = STATE_SNEK;
}

void fsm_evThanksTo(void){
	OLED_clear();
	OLED_store_menu(THANKS_TO_MENU);
	OLED_refresh();
	currentState = STATE_THANKS_TO;
}

OLED_line fsm_menuNavigate(OLED_line max_line){
	int last_dir_y = 0;
	int dir_y;
	int state_button;
	OLED_line currentLine = LINE_3;
	int last_state_button = 1;
	while(1){
		dir_y = JOY_get_dir_y();
		if (last_dir_y == MIDDLE && dir_y != MIDDLE && dir_y != UNDEFINED){
			if ((currentLine + dir_y) >= 2 && (currentLine + dir_y) <= max_line){	
				OLED_goto_line(currentLine);
				OLED_store_sym(' ');
				OLED_goto_line(currentLine += dir_y);
				OLED_store_sym('>');
				OLED_refresh();
			}	
		}
		if(dir_y != UNDEFINED){
			last_dir_y = dir_y;
		}
		state_button = JOY_get_button();
		if (last_state_button == 0 && state_button == 1){
			return currentLine;
		}
		last_state_button = state_button;
	}
}

//Loop until button press
void fsm_evReturn(void){
	uint8_t last_state_button = 1;
	while(1){
		if(JOY_get_button() && !last_state_button){
			return;
		} else if(!JOY_get_button()){
			last_state_button = 0;
		}
	}
}


