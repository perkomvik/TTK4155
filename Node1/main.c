/*
 * main.c
 *
 * Created: 30.08.2017 10:40:10
 *  Author: andersgd
 */ 

#include "fsm.h"

int main(void){	

	fsm_evInit();

	while (1){
		switch(fsm_getCurrentState()){
			case STATE_MAIN_MENU:
				switch(fsm_menuNavigate(LINE_5)){
					case(LINE_3):
						fsm_evPong();
						break;
					case(LINE_4):
						fsm_evSnek();
						break;
					case(LINE_5):
						fsm_evThanksTo();
						break;
					default:
						break;
				}
				break;
			case STATE_PONG:
				switch(fsm_menuNavigate(LINE_6)){
					case(LINE_3):
						pong_play(JOY);
						pong_print_highscore();
						fsm_Return();
						fsm_evPong();
						break;
					case(LINE_4):
						pong_play(SLIDER);
						fsm_Return();
						fsm_evPong();
						break;
					case(LINE_5):
						pong_print_highscore();
						fsm_Return();
						fsm_evPong();
						break;
					case(LINE_6):
						fsm_evMainMenu();
						break;
					default:
						break;
				}
				break;
			
			case STATE_SNEK:
				switch(fsm_menuNavigate(LINE_4)){
					case(LINE_3):
						//Do nothing
						break;
					case(LINE_4):
						fsm_evMainMenu();
						break;
					default:
						break;
				}
				break;
			case STATE_THANKS_TO:
				switch(fsm_menuNavigate(LINE_3)){
					case(LINE_3):
						fsm_evMainMenu();
						break;
					default:
						break;
				}
				break;
				
			default:
				break;
		}
	}
}