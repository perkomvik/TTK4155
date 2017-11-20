/*
 * Pong.h
 *
 * Created: 15.11.2017 10:50:41
 *  Author: mariuesk
 */ 


#ifndef PONG_H_
#define PONG_H_
#include "utilities.h"
#include "EEPROM.h"

typedef enum tag_game_mode{
	JOY = 0,
	SLIDER = 1
}game_mode; //??


//static char buffer[10] = "heeeeeeeee"; 

void pong_init(game_mode mode);
void pong_play(game_mode mode);
void pong_JOY(void);
void pong_slider(void);
void pong_update_score(uint8_t score);
void pong_print_highscore(void);
void pong_update_highscore(uint8_t score);
void pong_get_highscore_line(uint8_t score, uint8_t lineNum);
void pong_place_highscore(char* name, uint8_t score, uint8_t lineNum);
void print_struct(void);
void pong_save_highscore(void);
void pong_load_highscore(void);
void pong_highscore_init(void);

#endif /* PONG_H_ */