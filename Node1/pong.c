/*
 * Pong.c
 *
 * Created: 15.11.2017 10:50:31
 *  Author: mariuesk
 */ 


#include "pong.h"
#include "CAN_joystick.h"
#include "OLED.h"
#include "fsm.h"
//static uint8_t highscore[6] = {0};
	
typedef struct Highscores_template{
	char* name;
	uint8_t score;
}Highscores_template;

volatile static Highscores_template Highscore[6] =  {
{ "Marius    ",1},
{ "Marius    ",1},
{ "Marius    ",1},
{ "Marius    ",1},
{ "Marius    ",1},
{ "Marius    ",1}
};


void pong_update_score(uint8_t score){
	OLED_clear_line(5);
	OLED_goto_line(5);
	char myScore[16];
	sprintf(myScore, " Your score: %d", score);
	OLED_store_str(myScore);
	OLED_refresh();
}
void pong_init(game_mode mode){
	OLED_clear();
	OLED_store_menu(PLAYING_PONG_MENU);
	OLED_refresh();
	
	//send game mode instruction to node 2
	CAN_msg mode_msg;
	mode_msg.id = PONG_START; //id 0 means game_mode
	mode_msg.length = 1;
	mode_msg.data[0] = mode;
	CAN_message_send(&mode_msg);
}


void pong_play(game_mode mode){
	switch(mode){
		case(JOY):
			pong_JOY();
			break;
		case(SLIDER):
			pong_slider();
			break;
		default:
			break;
	}
}

void pong_JOY(void){
	pong_init(JOY);
	CAN_msg results;
	uint8_t game_over = 0;
	uint8_t score = 0;
	
	
	while (!game_over){
		
		if(CAN_receive(&results)){
			CAN_print(&results);
			if(results.data[0]){
				break;
			}
			send_all_joy(PONG_INSTR); //kan være problematisk å sende dette hvis spillet egt er ferdig
			
			if(results.data[1]){
				score++;
				pong_update_score(score);
			}
			//if(results.data[0]){
				//game_over = 1;
			//}
		}
	}
	fsm_evPong();
}

void pong_slider(void){
	pong_init(SLIDER);
	CAN_msg results;
	uint8_t game_over = 0;
	uint8_t score = 0;
	
	
	while (!game_over){
		
		if(CAN_receive(&results)){
			CAN_print(&results);
			if(results.data[0]){
				break;
			}
			send_all_slider(PONG_INSTR); //kan være problematisk å sende dette hvis spillet egt er ferdig
			
			if(results.data[1]){
				score++;
				pong_update_score(score);
			}
			//if(results.data[0]){
				//game_over = 1;
			//}
		}
	}
	
	fsm_evPong();
}

void pong_print_highscore(void){
	OLED_store_menu(HIGHSCORES_MENU);
	char str_num[3];
	
	for (uint8_t i = 0; i < 6; i++){
		if(Highscore[i].score == 0){
			break;
		}
		OLED_goto_line(i+1);
		printf("Senere navn: %s \n", Highscore[i].name);
		OLED_store_str(Highscore[i].name);
		OLED_store_sym(' ');
		itoa(Highscore[i].score,str_num,10);
		OLED_store_str(str_num);
	}
	OLED_refresh();
	fsm_evReturn();
	fsm_evMainMenu();
}

void pong_update_highscore(uint8_t score){
	for (uint8_t i = 0; i < 6; i++){
		if(score > Highscore[i].score){
			pong_get_highscore_line(Highscore[i].score, i);
		}else{
			fsm_evMainMenu();
		}
	}
}

void pong_get_highscore_line(uint8_t score, uint8_t lineNum){
	OLED_store_menu(CONGRATULATIONS_MENU);
	OLED_refresh();
	_delay_ms(1000);
	char name[10];
	scanf("%s",name); //may overflow
	char* name2 = "heeeeeeeei";
	sprintf(name2,name);
	printf("%s \n", name2);
	pong_place_highscore(name2,score,lineNum);
	
}



void pong_place_highscore(char* name, uint8_t score, uint8_t lineNum){
	for(uint8_t i = 5; i > lineNum; i--){
		Highscore[i-1].name = Highscore[i].name;
		Highscore[i-1].score = Highscore[i].score; 
	}
	printf("NAME: %s\t", name);
	Highscore[lineNum].name = name;
	printf("NAME IN list: %s\n", Highscore[lineNum].name);
	Highscore[lineNum].score = score;
}

//OLED_clear();
//print_OLED_string("Gz");
//OLED_goto_line(1);
//print_OLED_string("Save Highscore?");
//OLED_goto_line(2);
//print_OLED_symbol((char)ARROW);
//print_OLED_string("Yes");
//OLED_goto_line(3);
//print_OLED_string(" No"
