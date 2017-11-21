/*
 * SPI.c
 *
 * Created: 25.10.2017 12:37:07
 *  Author: mariuesk
 */ 

#include "SPI.h"

void SPI_MasterInit(){

	DDRB |= (1<<DDB0)|(1<< DDB7)|(1<<DDB1)|(1<<DDB2); // Set MOSI, SCK and SS output, all others input 
	SPCR |= (1<<MSTR)|(1<<SPR0)|(1<<SPE); // Enable Master, set clock rate fck/16 and enable SPI
}

char SPI_Read(){

	SPDR = 0xFF; // Send dummy byte to start transmission
	while(!(SPSR & (1<<SPIF))){} // Wait for finished transmission
	return SPDR; // Return data
}

void SPI_Send(char cData){

	SPDR = cData; // Send data
	while(!(SPSR & (1<<SPIF))){} // Wait for finished transmission
}