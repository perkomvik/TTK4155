/*
 * PID.h
 *
 * Created: 16.11.2017 13:25:48
 *  Author: mariuesk
 */ 


#ifndef PID_H_
#define PID_H_

#include "utilities.h"
#include "motor.h"

#define Kp 1
#define Ki 10
#define Kd 0.01
#define dt 0.016
//#define Kp 1
//#define Ki 0.5
//#define Kd 0.03

static int16_t rot_max;
static int16_t rot_min = 0;
static double integral = 0;
static int16_t prev_error = 0;

static volatile uint8_t timer_flag = 0;

void PID_init(void);
void PID(uint8_t pos_ref);
void PID_calibrate(void);
ISR(TIMER2_OVF_vect);

#endif /* PID_H_ */