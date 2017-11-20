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



void PlayPong(uint8_t mode);
void Pong_slider(void);
void Pong_joy(void);


#endif /* PONG_H_ */