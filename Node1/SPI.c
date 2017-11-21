/*
 * SPI.c
 *
 * Created: 04.10.2017 13:02:48
 *  Author: andersgd
 */ 
 #include "SPI.h"

 
 void SPI_master_init(void){

	 DDRB |= (1<<DDB5)|(1<< DDB7)|(1<<DDB4);  // Set MOSI, SCK and SS output, all others input
	 SPCR |= (1<<MSTR)|(1<<SPR0)|(1<<SPE); // Enable Master, set clock rate fck/16 and enable SPI
 }
 
 
 char SPI_read(){

	 SPDR = 0xFF; // Send dummy byte to start transmission
	 while(!(SPSR & (1<<SPIF))){} // Wait for finished transmission 
	 return SPDR; // Return data
 }

 void SPI_send(char cData){
 	
	 SPDR = cData; // Send data
	 while(!(SPSR & (1<<SPIF))){} // Wait for finished transmission
 }