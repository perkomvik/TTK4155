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
	pong_highscore_init();
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
	JOY_dir_y prev_dir_y = UNDEFINED;
	JOY_dir_y cur_dir_y;
	uint8_t last_state_button = 1;
	uint8_t cur_state_button;
	OLED_line cur_line = LINE_3;
	while(1){
		cur_dir_y = JOY_get_dir_y();
		if (prev_dir_y == MIDDLE && cur_dir_y != MIDDLE && cur_dir_y != UNDEFINED){
			if ((cur_line + cur_dir_y) >= 2 && (cur_line + cur_dir_y) <= max_line){	
				OLED_goto_line(cur_line);
				OLED_store_sym(' ');
				OLED_goto_line(cur_line += cur_dir_y);
				OLED_store_sym('>');
				OLED_refresh();
			}	
		}
		//Saturation for direction of y
		if(cur_dir_y != UNDEFINED){
			prev_dir_y = cur_dir_y;
		}
		//Prevent spamming presses across states
		cur_state_button = JOY_get_button();
		if (last_state_button == 0 && cur_state_button == 1){
			return cur_line;
		} else{
			last_state_button = cur_state_button;
		}	
	}
}

//Loop until button press with spam protection
void fsm_Return(void){
	uint8_t last_state_button = 1;
	while(1){
		if(JOY_get_button() && !last_state_button){
			return;
		} else if(!JOY_get_button()){
			last_state_button = 0;
		}
	}
}


