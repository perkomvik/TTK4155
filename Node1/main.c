/*
 * main.c
 *
 * Created: 30.08.2017 10:40:10
 *  Author: andersgd
 */ 
#include <avr/io.h>
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
						//fsm_evMenu2();
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



//printf("1 \n");
//printf("X: %d \t Y: %d \n", arr[0], arr[1]);






						//STATES
						//switch(fsm_getCurrentState()){
						//
						//
						//case STATE_MAIN_MENU:
						//switch(fsm_evMenuNavigate(5)){
						//case(2):
						//fsm_evMenu1();
						//break;
						//case(3):
						//fsm_evMenu2();
						//break;
						//case(4):
						//fsm_evMenu3();
						//break;
						//case(5):
						//fsm_evMenu4();
						//break;
						//}
						//break;
						//case STATE_MENU_1:
						//switch(fsm_evMenuNavigate(4)){
						//case(2):
						//fsm_evMenu1();
						//break;
						//case(3):
						//fsm_evMenu1();
						//break;
						//case(4):
						//fsm_evMainMenu();
						//break;
						//}
						//break;
						//case STATE_MENU_2:
						//switch(fsm_evMenuNavigate(3)){
						//case(2):
						//fsm_evMenu2();
						//break;
						//case(3):
						//fsm_evMainMenu();
						//break;
						//}
						//break;
						//case STATE_MENU_3:
						//switch(fsm_evMenuNavigate(3)){
						//case(2):
						//fsm_evMenu3();
						//break;
						//case(3):
						//fsm_evMainMenu();
						//break;
						//}
						//break;
						//case STATE_MENU_4:
						//switch(fsm_evMenuNavigate(3)){
						//case(2):
						//fsm_evMenu4();
						//break;
						//case(3):
						//fsm_evMainMenu();
						//break;
						//}
						//break;
						////}
						////break;
						//default:
						//break;
						//}

//menu_navigate();






//OLED_goto_line(0);
//print_OLED_string("1");

//SRAM_test();
//int arr[2] = {0};

