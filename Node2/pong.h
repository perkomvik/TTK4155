/*
 * Pong.h
 *
 * Created: 18.11.2017 11:58:51
 *  Author: mariuesk
 */ 


#ifndef PONG_H_
#define PONG_H_

#include "utilities.h"
#include "CAN.h"
#include "servo.h"
#include "IR.h"
#include "DAC.h"
#include "motor.h"
#include "solenoid.h"
#include "PID.h"

#define STOP 127

typedef enum tag_game_mode{
	JOY = 0,
	SLIDER = 1
}game_mode;

typedef enum tag_game_instructions{
	JOY_X = 0,
	JOY_Y = 1,
	JOY_B = 2
}game_instructions;

typedef enum tag_game_results{
	GAME_OVER = 0,
	GOAL = 1,
}game_results;


void pong_play(game_mode mode);
void pong_slider(void);
void pong_JOY(void);


#endif /* PONG_H_ */
