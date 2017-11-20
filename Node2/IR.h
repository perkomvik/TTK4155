/*
 * IR.h
 *
 * Created: 01.11.2017 11:18:11
 *  Author: mariuesk
 */ 


#ifndef IR_H_
#define IR_H_
#include "Utilities.h"
#include "ADC.h"



void IR_init(void);
void IR_MM(void);
void IR_calibrate(void);
uint8_t is_game_over(void);
uint8_t is_goal(void);





#endif /* IR_H_ */