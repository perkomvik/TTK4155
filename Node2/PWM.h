/*
 * PWM.h
 *
 * Created: 29.10.2017 12:06:57
 *  Author: mariuesk
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "utilities.h"

static uint16_t pwm_timer_freq;

void PWM_init(float period, uint32_t clock_freq);
void PWM_set_period(float period);
void PWM_pulse_set(float width);

#endif /* PWM_H_ */