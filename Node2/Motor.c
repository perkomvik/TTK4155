/*
 * Motor.c
 *
 * Created: 08.11.2017 12:18:21
 *  Author: mariuesk
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "Motor.h"
#include "DAC.h"
#include "CAN.h"

void motor_init(){
	
	// Enable motor
	set_bit(DDRH, PH4);
	set_bit(PORTH, PH4);
	
	// Set direction pin to output
	set_bit(DDRH, PH1);
	
	//--------------------Set encoder pins to output and input mode----------------------
	
	// Output Enable pin (active low): !OE
	set_bit(DDRB, PB5);
	
	//Selection pin: SEL
	set_bit(DDRH, PH3);
	
	// Set Reset pin: RST
	set_bit(DDRH, PH6);
	// Reset encoder
	motor_reset_encoder();
	
	// Set data bits to input:
	clear_bit(DDRK, PK0);
	clear_bit(DDRK, PK1);
	clear_bit(DDRK, PK2);
	clear_bit(DDRK, PK3);
	clear_bit(DDRK, PK4);
	clear_bit(DDRK, PK5);
	clear_bit(DDRK, PK6);
	clear_bit(DDRK, PK7);
	
	//motor_calibrate();
	
}


void motor_set_direction(motor_direction_t direction){
	//printf("Y value: %d \n", direction);
	switch (direction > 121){
		case(LEFT):
			clear_bit(PORTH, PH1);
			break;
		case(RIGHT):
			set_bit(PORTH, PH1);
			break;
	}
}

void motor_set_speed(uint8_t speed){
	//printf("Y value: %d \n", speed);
	switch (speed > 126){
		case(LEFT):
			DAC_send(126-speed);
			break;
		case(RIGHT):
			DAC_send(speed-127);
			break;
		default:
			DAC_send(speed-127);
			break;
	}
}

void motor_set_speed_2(uint8_t speed){
		DAC_send(speed);
}

void motor_reset_encoder() {
	clear_bit(PORTH, PH6);
	_delay_us(200);
	set_bit(PORTH, PH6);
}

int16_t motor_read_rotation(uint8_t reset_flag){
	
	/*-------------------------------------------------*
	 |	    clear/set SEL opposite of datasheet        |
	 |  We don't know why, perhaps faulty motor box?   |
	 *-------------------------------------------------*/
	
	//Set !OE low to enable output of encoder jumps PH5
	clear_bit(PORTB, PB5);
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_us(60);
	
	//Read LSB
	uint8_t low = PINK;
	//printf("Low: %d\n", low);
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	
	//Wait about 20 microseconds
	_delay_us(60);
	
	//Read MSB
	uint8_t high = PINK;
	//printf("High: %d\n", high);
	if (reset_flag) {
 		//Toggle !RST to reset encoder
		motor_reset_encoder();
	}
	//Set !OE high to disable output of encoder
	set_bit(PORTB, PB5);
	
	int16_t rot = (int16_t) ( (high << 8) | low);
	
	return rot;
}

void motor_calibrate() {
	motor_set_direction(21);
	motor_set_speed(0);
	int16_t cur_rot = motor_read_rotation(1);
	int16_t prev_rot = cur_rot+200;
	while(prev_rot != cur_rot) {
		printf("Encoder prev: %d\t",prev_rot);
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_read_rotation(0);
		
		printf("Encoder cur: %d\n",prev_rot);
	}
	motor_set_speed(126);
	_delay_ms(500);
	motor_reset_encoder();
	
	
}

void motor_move(int16_t diff_rot, uint8_t power) {
	if (diff_rot > 100) {
		motor_set_direction(RIGHT);
		motor_set_speed(power);
	}
	else if (diff_rot < -100) {
		motor_set_direction(RIGHT);
		motor_set_speed(power);
	}
	else {
		motor_set_speed(0);
	}
}

motor_encoder_test(void){
	printf("Encoder: %d\n", motor_read_rotation(0));
}