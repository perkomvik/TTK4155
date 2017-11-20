/*
 * PWM.c
 *
 * Created: 29.10.2017 12:06:45
 *  Author: mariuesk
 */ 

#include "PWM.h"
static uint16_t pwm_timer_freq;

void PWM_init(float period, uint32_t clock_freq){
	uint16_t prescaler = 256;
	
	//Fast PWM-MODE (mode 14, table 17-2)
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11);
	clear_bit(TCCR1A, WGM10);
	
	//Set compare output on PB6 (OC1B)
	set_bit(TCCR1A, COM1B1);
	clear_bit(TCCR1A, COM1B0);
	pwm_timer_freq = (uint32_t)clock_freq/prescaler;
	PWM_set_period(period);
	

	// Set PB6 to output mode
	set_bit(DDRB, PB6);
}

void PWM_set_period(float period){
	
	// Set prescaler 256
	set_bit(TCCR1B, CS12);
	clear_bit(TCCR1B, CS11);
	clear_bit(TCCR1B, CS10);
	
	// Set period to 20 ms (prescaler 256)
	uint16_t top = pwm_timer_freq*period;
	ICR1 = top;
	
}

void PWM_pulse_set(float width) {
	
	uint16_t pulse = pwm_timer_freq*width-0.5;
	//printf("Width: %d \t Pulse: %d \n",width, pulse);
	
	OCR1B = pulse;
}