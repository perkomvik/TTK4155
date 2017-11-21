/*
 * PWM.c
 *
 * Created: 29.10.2017 12:06:45
 *  Author: mariuesk
 */ 

#include "PWM.h"

void PWM_init(float period, uint32_t clock_freq){
	uint16_t prescaler = 256; //Chosen to achieve higher resolution
	
	//Fast PWM
	set_bit(TCCR1B, WGM13); // Timer/Counter 1 Control Register B
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11); // Timer/Counter 1 Control Register A
	clear_bit(TCCR1A, WGM10);
	
	//Clear OC1B on compare match, set OC1B at BOTTOM (non-inverting mode)
	set_bit(TCCR1A, COM1B1);
	clear_bit(TCCR1A, COM1B0);
	pwm_timer_freq = (uint32_t)clock_freq/prescaler;
	PWM_set_period(period);
	
	// Set PB6/OC1B to output mode
	set_bit(DDRB, PB6);
}

void PWM_set_period(float period){
	
	// Set prescaler 256
	set_bit(TCCR1B, CS12);
	clear_bit(TCCR1B, CS11);
	clear_bit(TCCR1B, CS10);
	
	// Set period to 20 ms (prescaler 256)
	uint16_t top = (uint16_t)pwm_timer_freq*period;
	ICR1 = top;
}

void PWM_pulse_set(float width) {
	
	uint16_t pulse = pwm_timer_freq*width-0.5;
	OCR1B = pulse;
}