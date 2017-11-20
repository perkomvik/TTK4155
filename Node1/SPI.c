/*
 * SPI.c
 *
 * Created: 04.10.2017 13:02:48
 *  Author: andersgd
 */ 
 #include "SPI.h"

 
 void SPI_master_init(void){
	 /* Set MOSI and SCK output, all others input */
	 DDRB |= (1<<DDB5)|(1<< DDB7)|(1<<DDB4); // må ha med en til slave greie pb0 og pb7 i node 2?
	 /* Enable SPI, Master, set clock rate fck/16 */
	 SPCR = (1<<MSTR)|(1<<SPR0);
	 SPCR |= (1<<SPE);
 }
 
 
 char SPI_read(){
	 /* Start transmission */
	 SPDR = 0xFF;
	 /* Wait for transmission complete */
	 while(!(SPSR & (1<<SPIF))){}
	 return SPDR;
 }

 void SPI_send(char cData){
	 /* Start transmission */
	 SPDR = cData;
	 /* Wait for transmission complete */
	 while(!(SPSR & (1<<SPIF))){}
 }