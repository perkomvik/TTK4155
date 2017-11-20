/*
 * Pong.h
 *
 * Created: 15.11.2017 10:50:41
 *  Author: mariuesk
 */ 


#ifndef PONG_H_
#define PONG_H_
#include "Utilities.h"
void Pong_init(uint8_t);
void PlayPong(void);
void PlayPong2(uint8_t mode);
void Pong_joy(void);
void Pong_slider(void);
void update_score(uint8_t score);
void print_Highscore(void);
void update_Highscore(score);
void get_highscore_line(uint8_t score, uint8_t lineNum);
void place_Highscore(char* name, uint8_t score, uint8_t lineNum);


#endif /* PONG_H_ */