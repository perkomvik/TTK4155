/*
 * SPI.c
 *
 * Created: 25.10.2017 12:37:07
 *  Author: mariuesk
 */ 

#include "SPI.h"
#include "Utilities.h"
void SPI_MasterInit(){
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<DDB0)|(1<< DDB7)|(1<<DDB1)|(1<<DDB2); // Setter outputs som rikitg 
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<MSTR)|(1<<SPR0);
	SPCR |= (1<<SPE);
}

char SPI_Read(){
	/* Start transmission */
	SPDR = 0xFF;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){}
	return SPDR;
}

void SPI_Send(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))){}
}