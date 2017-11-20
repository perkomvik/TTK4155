/*
 * joystick.c
 *
 * Created: 13.09.2017 17:17:27
 *  Author: perkom
 */ 

#include "joystick.h"
#include "ADC.h"

void JOY_init(void){
	set_bit(PORTD, PIND5); // Set pin to input
}


uint8_t JOY_get_button(void){
	return 1 > test_bit(PIND, PIND5); // Check if button is pressed
}

void JOY_get_pos(int arr[]){
	arr[0] = ADC_read(CHANNEL_1); 
	arr[1] = ADC_read(CHANNEL_2);
}

uint8_t JOY_get_x(void){
	uint8_t x = ADC_read(CHANNEL_1);
	if (x > 145 || x < 123){
		return x;
	}
	else {
		return 127; //Stabilized Centered Value
	}
}

uint8_t JOY_get_y(void){
	uint8_t y = ADC_read(CHANNEL_2);
	if (y > 145 || y < 123){
		return y;
	}
	else {
		return 127; //Stabilized Centered Value
	}
}

JOY_dir_y JOY_get_dir_y(void){
	uint8_t y = ADC_read(CHANNEL_2);
	if (y < 5){
		return DOWN;
	} else if (y > 250){
		return UP;
	} else if (y < 134 && y > 124){
		return MIDDLE;
	}
	else{
		return UNDEFINED; 
	}
}

uint8_t left_slider_pos(void){
	return ADC_read(CHANNEL_3);
}

uint8_t right_slider_pos(void){
	return ADC_read(CHANNEL_4);
}

uint8_t right_button(void){
	return 0 < test_bit(PIND, PIND4); // Check if right button is pressed
}

uint8_t left_button(void){
	return 0 < test_bit(PIND, PIND3); // Check if left button is pressed
}
