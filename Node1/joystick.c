/*
 * joystick.c
 *
 * Created: 13.09.2017 17:17:27
 *  Author: perkom
 */ 

#include "joystick.h"
#include "ADC.h"

void JOY_init(void){
	set_bit(PORTD, PIND5); //joystick pullup
}


uint8_t JOY_get_button(void){
	return 1 > test_bit(PIND, PIND5); //did not return 1/0
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
	printf("Y: %d\n", y);
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
	return 0 < test_bit(PIND, PIND4); // did not return 0/1
}

uint8_t left_button(void){
	return 0 < test_bit(PIND,PIND3); // did not return 0/1
}
