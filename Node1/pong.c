/*
 * Pong.c
 *
 * Created: 15.11.2017 10:50:31
 *  Author: mariuesk
 */ 


#include "pong.h"


	
typedef struct Highscores_template{
	char* name;
	uint8_t score;
}Highscores_template;

static volatile Highscores_template Highscore[6] =  {
{ "AAAAAAAAAA",6},
{ "BBBBBBBBBB",5},
{ "CCCCCCCCCC",4},
{ "DDDDDDDDDD",3},
{ "EEEEEEEEEE",2},
{ "FFFFFFFFFF",1}
};



void pong_update_score(uint8_t score){
	uint8_t i;
	OLED_clear_line(5);
	OLED_goto_line(5);
	char myScore[16];
	sprintf(myScore, " Your score: %d", score);
	OLED_store_str(myScore);
	for (i = 0; (Highscore[i].score >= score && i < 6); i++){
		_delay_us(10);
	}
	if(i != 6 ){
		OLED_clear_line(6);
		OLED_goto_line(6);
		sprintf(myScore, " Position: %d", i+1);
		OLED_store_str(myScore);
	}
	OLED_refresh();
}
void pong_init(game_mode mode){	
	
	CAN_msg mode_msg;
	mode_msg.id = PONG_START; 
	mode_msg.length = 1;
	mode_msg.data[0] = mode;
	CAN_message_send(&mode_msg);
	switch(mode){
		case JOY:
			OLED_loading_screen();
			break;
		case SLIDER:
			OLED_loading_screen_long();
			break;
	}

	OLED_clear();
	OLED_store_menu(PLAYING_PONG_MENU);
	if(Highscore[0].score > 0){
		OLED_goto_line(LINE_4);
		char top_player[16];
		sprintf(top_player, " %s  %d", Highscore[0].name, Highscore[0].score);
		OLED_store_str(top_player);
	}
	OLED_refresh();
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
	uint8_t score = 0;
	
	while (1){
		
		if(CAN_receive(&results)){
			if(results.data[GAME_OVER]){
				break;
			}
			send_all_joy(PONG_INSTR);
			if(results.data[GOAL]){
				score++;
				pong_update_score(score);
			}
		}
	}
	OLED_game_over_screen();
	pong_update_highscore(score);

}



void pong_slider(void){
	pong_init(SLIDER);
	CAN_msg results;
	uint8_t score = 0;
	
	while (1){
		if(CAN_receive(&results)){
			if(results.data[GAME_OVER]){
				break;
			}
			send_all_slider(PONG_INSTR); //kan være problematisk å sende dette hvis spillet egt er ferdig
			if(results.data[GOAL]){
				score++;
				pong_update_score(score);
			}
		}
	}
	OLED_game_over_screen();
	pong_update_highscore(score);

}

void pong_print_highscore(void){
	OLED_store_menu(HIGHSCORES_MENU);
	char str_num[3];
	
	for (uint8_t i = 0; i < 6; i++){
		if(Highscore[i].score == 0){
			break;
		}
		OLED_goto_line(i+1);
		OLED_store_str(Highscore[i].name);
		OLED_store_str("   ");
		itoa(Highscore[i].score,str_num,10);
		OLED_store_str(str_num);
	}
	OLED_refresh();
}

void pong_update_highscore(uint8_t score){
	for (uint8_t i = 0; i < 6; i++){
		if(score > Highscore[i].score){
			pong_get_highscore_line(score, i);
			pong_save_highscore();
			break;
		}
	}
	
}

void pong_get_highscore_line(uint8_t score, uint8_t lineNum){
	OLED_store_menu(CONGRATULATIONS_MENU);
	OLED_refresh();
	char buffer[10];
	scanf("%s",buffer);
	pong_place_highscore(buffer,score,lineNum);
	
}

void pong_place_highscore(char* name, uint8_t score, uint8_t lineNum){
	for(uint8_t i = 5; i > lineNum; i--){
		for(uint8_t b = 0; b < 10; b++){
			Highscore[i].name[b] = Highscore[i-1].name[b];
		}
		Highscore[i].score = Highscore[i-1].score; 
	}
	//Can not directly copy from scanf buffer
	char buffer[10] = "          ";
	for(int i = 0;  name[i] != '\0'; i++){
		buffer[i] = name[i];
	}
	for(int i = 0;  i < 10; i++){
		Highscore[lineNum].name[i] = buffer[i];
	}
	Highscore[lineNum].score = score;
}


void pong_save_highscore(void){
	unsigned int adr = 0; 
	for(uint8_t i = 0; i < 6; i++){
		for(uint8_t j = 0; j < 10; j++){
			EEPROM_write(adr,Highscore[i].name[j]);
			adr++;
		}
		EEPROM_write(adr, Highscore[i].score);
		adr++;
	} 
}
void pong_load_highscore(void){
	unsigned int adr = 0;
	for(uint8_t i = 0; i < 6; i++){
		for(uint8_t j = 0; j < 10; j++){
			Highscore[i].name[j] = EEPROM_read(adr);
			adr++;
		}
		Highscore[i].score = EEPROM_read(adr);
		adr++;
	}
}

void pong_highscore_init(void){
	pong_load_highscore();
}

void print_highscore_struct(void){
	for (uint8_t i = 0; i < 6; i++){
		printf("%s\t", Highscore[i].name);
	}
	printf("\n");
}