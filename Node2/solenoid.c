/*
 * solenoid.c
 *
 * Created: 12.11.2017 12:17:09
 *  Author: mariuesk
 */ 

#include "solenoid.h"

void solenoid_init(void){
	//initialize PB4 as output, PB4 = ?
	set_bit(DDRB,PB4);
	PORTB |= (1 << PB4);
}

void solenoid_fire(uint8_t button){

		if(button){
		PORTB &= ~(1<<PB4);
		} else{
		PORTB |= (1<<PB4);
		}

}

