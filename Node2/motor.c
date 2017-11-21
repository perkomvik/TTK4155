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
	
	//--------------------Set encoder pins to output and input mode----------------------//
	
	// Enable control for output enable. Remember: active low - !OE
	set_bit(DDRB, PB5);
	
	// Enable control for selection pin: SEL
	set_bit(DDRH, PH3);
	
	// Enable control for Reset pin: RST
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
	
}


void motor_set_direction(motor_direction_t direction){

	switch (direction > 121){
		case(LEFT): // LEFT is 0-127, 121 is selected to have a defined value for the middle
			clear_bit(PORTH, PH1);
			break;
		case(RIGHT): // RIGHT is 128-255
			set_bit(PORTH, PH1);
			break;
	}
}

void motor_set_speed(uint8_t speed){
	motor_set_direction(speed);
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
	clear_bit(PORTH, PH6); // Set active low reset
	_delay_us(200);
	set_bit(PORTH, PH6); // Finish reset
}

int16_t motor_read_rotation(uint8_t reset_flag){

	//Set !OE low to enable output of encoder. Defect PH5, used PB5
	clear_bit(PORTB, PB5);
	
	//Set SEL high to get low byte
	set_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read LSB
	uint8_t low = PINK; //
	
	//Set SEL low to get high byte
	clear_bit(PORTH, PH3);
	
	_delay_us(60);
	
	//Read MSB
	uint8_t high = PINK;

	if (reset_flag) {
		motor_reset_encoder();
	}

	//Set !OE high to disable output of encoder
	set_bit(PORTB, PB5);
	
	int16_t rot = (int16_t) ( (high << 8) | low);
	
	return rot;
}

motor_encoder_test(void){
	printf("Encoder: %d\n", motor_read_rotation(0));
}
