/*
 * joystick.c
 *
 * Created: 13.09.2017 17:17:27
 *  Author: perkom
 */ 

#include "joystick.h"
#include "ADC.h"

void JOY_init(){
	//clear_bit(DDRD, 2); //middle joytstick button
	set_bit(PORTD, 5); //joystick pullup
	//clear_bit(DDRD,3); //left button
	//clear_bit(DDRD, 4);  //right button
	
	//clear_bit() add joystick button
}

void JOY_calibrate(){
	
}

int JOY_get_button(){
	//printf("Joystick button status: %d\n" , CHECKBIT(PIND, PIND5));
	return 1 > CHECKBIT(PIND, PIND5);
}

void JOY_get_pos(int arr[]){
	arr[0] = ADC_read(1);
	arr[1] = ADC_read(2);
}

uint8_t JOY_get_pos_x(){
	uint8_t x = ADC_read(1);
	if (x > 145){
		return x;
	}
	else if (x < 123){
		return x;
	}
	else return 127;
}

uint8_t JOY_get_pos_y(){
	uint8_t y = ADC_read(2);
	if (y > 145){
		return y;
	}
	else if (y < 123){
		return y;
	}
	else return 127;
}

char* JOY_get_dir(){
	int arr[2] = {0};
	JOY_get_pos(arr);
	if (arr[0] < 123){
		return "LEFT";
	} else if (arr[0] > 132){
		return "RIGHT";
	} else {
		return "MIDDLE";
	}	
}



int JOY_get_dir_x(){
	int x = ADC_read(1);
	if (x < 123){
		return LEFT;
	} else if (x > 136){
		return RIGHT;
	} else {
		return MIDDLE;
	}
}

int JOY_get_dir_y(){
	int y = ADC_read(2);
	if (y < 100){
		return DOWN;
	} else if (y > 170){
		return UP;
	} else {
		return MIDDLE;
	}
}

int left_slider_pos(){
	return ADC_read(3);
}

int right_slider_pos(){
	return ADC_read(4);
}

int right_button(){
	return 0 < CHECKBIT(PIND, PIND4);
}

int left_button(){
	return 0 < CHECKBIT(PIND,3);
}
