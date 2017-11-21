/*
 *	ADC.c
 *
 * Created: 01.11.2017 11:16:59
 *  Author: mariuesk
 */ 

#include "ADC.h"

void ADC_init(void){
	clear_bit(DDRF, PF0); // Channel 0 for the ADC will be used, = PF0 = A0 = input
	clear_bit(DDRF, PF1); // Channel 0 for the ADC will be used, = PF0 = A0 = input
	set_bit(ADCSRA, ADEN); // ADC Control and Status Register A - Enable ADC, next coversion takes 25 adc clock cycles
	
	// Set prescaler to 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	// Set voltage reference to 2.56V
	set_bit(ADMUX, REFS1);
	set_bit(ADMUX, REFS0);
}

uint16_t ADC_read(void){
	set_bit(ADCSRA, ADSC); // Start single conversion
	loop_until_bit_is_set(ADCSRA, ADIF); // Wait for interrupt flag to be set
	uint8_t data_low = ADCL; // Low data bits of converted data
	uint16_t data_high = ADCH; // High data bits of converted data
	uint16_t data = (data_high << 8)|(data_low); // Combining low and high
	return data;
}

uint16_t ADC_read_channel(ADC_channel channel){
	switch(channel){
		case(CHANNEL_0):
			clear_bit(ADMUX,MUX0);
			return ADC_read();
		case(CHANNEL_1):
			set_bit(ADMUX,MUX0); 
			return ADC_read();
		default:
			return 0;
	}
}