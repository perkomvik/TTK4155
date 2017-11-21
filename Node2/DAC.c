/*
 * DAC.c
 *
 * Created: 08.11.2017 12:00:45
 *  Author: mariuesk
 */ 

#include "DAC.h"

void DAC_init() {
	sei();
	TWI_Master_Initialise();

}

void DAC_send(uint8_t data){
	uint8_t address = 0b01010000; // Set slave address
	uint8_t command = 0b0; // Setting DAC0 output
	
	uint8_t message[3];
	message[0] = address;
	message[1] = command;
	message[2] = data;
	
	TWI_Start_Transceiver_With_Data(message, 3);
}