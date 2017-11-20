/*
 * ADC.c
 *
 * Created: 13.09.2017 12:11:02
 *  Author: perkom
 */ 

#include "ADC.h"


uint8_t ADC_read(ADC_channel channel){ 

	volatile char * a = (char*) ADC_MEM_ADR; //Create pointer mapped to ADC
	uint8_t result;

	switch(channel){
		case CHANNEL_1: // Read X-input joystick
			*a = 4;
			_delay_us(60);
			result =*a;
			break;

		case CHANNEL_2: // Read Y-input joystick
			*a = 5;
			_delay_us(60);
			result =*a;
			break;

		case CHANNEL_3: // Read left slider
			*a = 6;
			_delay_us(60);
			result =*a;
			break;

		case CHANNEL_4: // Read right slider
			*a = 7;
			_delay_us(60);
			result =*a;
			break;

		default:
			result = 0;
			break;
	}
	return result;
}