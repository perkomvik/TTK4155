/*
 * servo.h
 *
 * Created: 29.10.2017 12:39:26
 *  Author: mariuesk
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#include "Utilities.h"
#include "PWM.h"
void servo_init(uint32_t clock_freq);
void set_servo(uint8_t servo_dir);

#endif /* SERVO_H_ */