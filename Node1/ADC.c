/*
 * ADC.c
 *
 * Created: 13.09.2017 12:11:02
 *  Author: perkom
 */ 

#include "ADC.h"


uint8_t ADC_read(int channel){ 

	
	volatile char * a = (char*) 0x1400;

	
	uint8_t result;

	switch(channel){
		
		case(1): // Enable Channel 1 //Read X-input joystick
			
			*a = 4;
			_delay_us(60);
			result =*a;
			break;
		case(2): // Enable Channel 2 //Read Y-input joystick
			
			*a = 5;
			_delay_us(60);
			result =*a;
			break;
		case(3): // Enable Channel 3 // read left slider
			*a = 6;
			_delay_us(60);
			result =*a;
			break;
		case(4): // Enable Channel 4 // read right slider
			*a = 7;
			_delay_us(60);
			result =*a;
			break;
		default:
			return 0;
		
	}
	
	
	return result;
	
}