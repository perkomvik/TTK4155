/*
 * menu.c
 *
 * Created: 27.09.2017 13:03:58
 *  Author: mariuesk
 */ 
#define status_x 0
#define status_y 1
#define status_button 2

#include "fsm.h"

//static uint8_t currentState;

int fsm_getCurrentState(){
	return currentState;
}



void fsm_evInit(){
	USART_Init();
	init_memory();
	_delay_us(100);
	//SRAM_test();
	_delay_us(100);
	JOY_init();
	OLED_init();
	CAN_init(MODE_NORMAL);
	
	
	fsm_evMainMenu();
}

void fsm_evMainMenu(){
	print_OLED_string(MAIN_MENU);
	OLED_refresh();
	currentState = STATE_MAIN_MENU;
}

void fsm_evPong(){
	print_OLED_string(PONG_MENU);
	OLED_refresh();
	currentState = GAME;
}

void fsm_evSnek(){
	print_OLED_string(SNEK_MENU);
	OLED_refresh();
	currentState = SNEK;
}

void fsm_evThanksTo(){
	print_OLED_string(THANKS_TO_MENU);
	OLED_refresh();
	currentState = THANKS_TO;
}


int fsm_evMenuNavigate(int numLines){
	int last_dir_y = 0;
	int dir_y;
	int state_button;
	int currentLine = 2;
	int last_state_button = 1;
	while(1){
		dir_y = JOY_get_dir_y();
		if (last_dir_y == MIDDLE && dir_y != MIDDLE){
			if ((currentLine + dir_y) >= 2 && (currentLine + dir_y) <= numLines){	
				OLED_goto_line(currentLine);
				print_OLED_symbol((char)32);
				OLED_goto_line(currentLine += dir_y);
				print_OLED_symbol((char)ARROW);
				OLED_refresh();
			}	
		} 
		last_dir_y = dir_y;
		state_button = JOY_get_button();
		if (last_state_button == 0 && state_button == 1){
			return currentLine;
		}
		last_state_button = state_button;
	}
}

void fsm_evReturn(void){
	int last_state_button = 1;
	while(1){
		if(JOY_get_button() && !last_state_button){
			return;
		} else if(!JOY_get_button()){
			last_state_button = 0;
		}
		
	}
}


