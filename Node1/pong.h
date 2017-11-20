/*
 * Pong.h
 *
 * Created: 15.11.2017 10:50:41
 *  Author: mariuesk
 */ 


#ifndef PONG_H_
#define PONG_H_
#include "Utilities.h"
typedef enum tag_game_mode game_mode; //??

void pong_init(game_mode mode);
void pong_play(game_mode mode);
void pong_JOY(void);
void pong_slider(void);
void pong_update_score(uint8_t score);
void pong_print_highscore(void);
void pong_update_highscore(uint8_t score);
void pong_get_highscore_line(uint8_t score, uint8_t lineNum);
void pong_place_highscore(char* name, uint8_t score, uint8_t lineNum);


#endif /* PONG_H_ */