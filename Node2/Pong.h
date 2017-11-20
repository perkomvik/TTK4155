/*
 * Pong.h
 *
 * Created: 18.11.2017 11:58:51
 *  Author: mariuesk
 */ 


#ifndef PONG_H_
#define PONG_H_

#include "Utilities.h"
#include "CAN.h"
#include "servo.h"
#include "IR.h"
#include "DAC.h"
#include "Motor.h"
#include "solenoid.h"
#include "PID.h"

typedef enum tag_game_mode{
	JOY = 0,
	SLIDER = 1
}game_mode;


void pong_play(game_mode mode);
void pong_slider(void);
void pong_JOY(void);


#endif /* PONG_H_ */