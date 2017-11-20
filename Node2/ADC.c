/*
 *	ADC.c
 *
 * Created: 01.11.2017 11:16:59
 *  Author: mariuesk
 */ 

#include "ADC.h"

void ADC_init(void){
	clear_bit(DDRF, PF0); //Channel 0 for the ADC will be used, = PF0 = A0 = input
	clear_bit(DDRF, PF1); //Channel 0 for the ADC will be used, = PF0 = A0 = input
	set_bit(ADCSRA,ADEN); // Enable ADC, next coversion takes 25 adc clock cycles
	
	// Set prescaler to 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	// Set voltage reference to 2.56V
	set_bit(ADMUX,REFS1);
	set_bit(ADMUX,REFS0);
}

uint16_t ADC_read(void){
	//channel 0 is default
	set_bit(ADCSRA,ADSC); //start single conversion, takes 13 adc clokc cycles
	loop_until_bit_is_set(ADCSRA,ADIF); // wait for coversion to be finished
	uint8_t data_low = ADCL;
	uint16_t data_high = ADCH;
	uint16_t data = (data_high << 8)|(data_low); //combining low and high
	return data;
}

uint16_t ADC_read_channel(uint8_t channel){
	switch(channel){
		case(0):
			clear_bit(ADMUX,MUX0); //Channel 0
			return ADC_read();
		case(1):
			set_bit(ADMUX,MUX0); //Channel 1
			return ADC_read();
		default:
			return 0;
	}
}