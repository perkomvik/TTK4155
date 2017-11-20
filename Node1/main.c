/*
 * main.c
 *
 * Created: 30.08.2017 10:40:10
 *  Author: andersgd
 */ 

#include "fsm.h"

int main(void){	
	
	fsm_evInit();
	
	//USART_test();
	//printf("Node 1 start\n");
	while (1){
		//printf("HEi\n");
		switch(fsm_getCurrentState()){
			case STATE_MAIN_MENU:
				switch(fsm_evMenuNavigate(4)){
					case(2):
					//get_highscore_line(8,3);
						fsm_evPong();
						break;
					case(3):
						fsm_evSnek();
						break;
					case(4):
						//fsm_evThanksTo();
						get_highscore_line(10,0);
						fsm_evPong();
						break;
					default:
						break;
				}
				break;
			case GAME:
				switch(fsm_evMenuNavigate(5)){
					case(2):
						PlayPong2(JOY);
						break;
					case(3):
						//PlayPong2(SLIDER);
						break;
					case(4):
						print_Highscore();
						break;
					case(5):
						fsm_evMainMenu();
						break;
					default:
						break;
				}
				break;
			
			case SNEK:
				switch(fsm_evMenuNavigate(3)){
					case(2):
						//fsm_evMenu2();
						break;
					case(3):
						fsm_evMainMenu();
						break;
					default:
						break;
				}
				break;
			case THANKS_TO:
				switch(fsm_evMenuNavigate(2)){
					case(2):
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



//OLED_clear();
//OLED_fill();
//print_OLED_string("8--------D");
//printf("X: %d \t Y: %d \n", JOY_get_dir_x(), JOY_get_dir_y());
//OLED_clear();
//OLED_fill();
//_delay_ms(100);
//OLED_goto_line(2);
//*a = 0x00;
//JOY_get_pos(arr);
//printf("X: %d \t Y: %d \n", arr[0], arr[1]);
//printf(left_slider_pos());
//printf(right_slider_pos());
//printf("DIR: %s \n", JOY_get_dir());
//printf("left button: %d \t", left_slider_pos());
//printf("right button: %d \n", right_slider_pos());
//