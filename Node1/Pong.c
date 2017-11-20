/*
 * Pong.c
 *
 * Created: 15.11.2017 10:50:31
 *  Author: mariuesk
 */ 


#include "Pong.h"
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
{ "Marius    ",1},
};


void update_score(uint8_t score){
	OLED_clear_line(5);
	OLED_goto_line(5);
	char myScore[16];
	sprintf(myScore, "Your Score: %d", score);
	print_OLED_string(myScore);
	OLED_refresh();
}
void Pong_init(uint8_t mode){
	OLED_clear();
	print_OLED_string("   PONGO");
	OLED_goto_line(2);
	print_OLED_string("Highscore:");
	OLED_goto_line(3);
	print_OLED_string("Marius - 255");
	OLED_goto_line(5);
	print_OLED_string("Your Score: 0");
	OLED_goto_line(6);
	print_OLED_string("Position: N/A");
	OLED_refresh();
	
	//send game mode instruction to node 2
	CAN_message game_mode;
	game_mode.id = 0; //id 0 means game_mode
	game_mode.length = 1;
	game_mode.data[0] = mode;
	CAN_message_send(&game_mode);
}
void PlayPong(void){
	//Pong_init();
	//CAN_message results;
	//uint8_t score = 1;
	//uint8_t game_over = 0;
	//
	//while (!game_over){
		//
		//if(CAN_receive(&results)){ 
			//send_all(2); //kan være problematisk å sende dette hvis spillet egt er ferdig
			//
			//if(scores.data[0]){
				//score++;
				////update_score(score);
			//}
			//if(scores.data[1]){
				////game_over = 1;
			//}
		//}
	//}
	//fsm_evPong();
	////update_Highscore(score);
}

void PlayPong2(uint8_t mode){
	switch(mode){
		case(JOY):
			Pong_joy();
			break;
		case(SLIDER):
			Pong_slider();
			break;
		default:
			break;
	}
}


void Pong_joy(void){
	Pong_init(JOY);
	CAN_message results;
	uint8_t game_over = 0;
	uint8_t score = 0;
	
	while (!game_over){
		
		if(CAN_receive(&results)){
			send_all_joy(2); //kan være problematisk å sende dette hvis spillet egt er ferdig
			
			if(results.data[1]){
				score++;
				update_score(score);
			}
			if(results.data[1]){
				//game_over = 1;
				if(score > 20){
					game_over = 1;
				}
			}
		}
	}
	
	fsm_evPong();
}

void Pong_slider(void){
	Pong_init(SLIDER);
	CAN_message results;
	uint8_t game_over = 0;
	uint8_t score = 0;
	
	
	while (!game_over){
		
		if(CAN_receive(&results)){
			send_all_slider(2); //kan være problematisk å sende dette hvis spillet egt er ferdig
			
			if(results.data[1]){
				score++;
				update_score(score);
			}
			if(results.data[1]){
				if(score > 20){
					game_over = 1;
				}
			}
		}
	}
	
	fsm_evPong();
}

void print_Highscore(void){
	print_OLED_string(HIGHSCORES_MENU);
	char str_num[3];
	
	for (uint8_t i = 0; i < 6; i++){
		if(Highscore[i].score == 0){
			break;
		}
		OLED_goto_line(i+1);
		printf("Senere navn: %s \n", Highscore[i].name);
		print_OLED_string(Highscore[i].name);
		print_OLED_symbol(' ');
		itoa(Highscore[i].score,str_num,10);
		print_OLED_string(str_num);
	}
	OLED_refresh();
	fsm_evReturn();
	fsm_evPong();
}

void update_Highscore(score){
	for (uint8_t i = 0; i < 6; i++){
		if(score > Highscore[i].score){
			get_highscore_line(Highscore[i].score, i);
		}else{
			fsm_evMainMenu();
		}
	}
}

void get_highscore_line(uint8_t score, uint8_t lineNum){
	print_OLED_string(CONGRATULATIONS_MENU);
	OLED_refresh();
	_delay_ms(1000);
	char name[10];
	scanf("%s",name); //may overflow
	char* name2;
	sprintf(name2,name);
	printf("%s \n", name2);
	place_Highscore(name2,score,lineNum);
	
}



void place_Highscore(char* name, uint8_t score, uint8_t lineNum){
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
