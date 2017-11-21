/*
 * Usart_Driver.c
 *
 * Created: 18.10.2017 18:39:31
 *  Author: mariuesk
 */ 

#include "USART.h"


void USART_Init(void){
	/* Set baud rate */
	uint16_t ubrr = F_CPU / 16 / BAUD - 1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter 
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); // Set frame format: 8data, 2stop bit
	fdevopen(USART_Transmit, USART_Receive);
	
}

int USART_Transmit( unsigned char data ){ //Definert som void i node 1??

	while ( !( UCSR0A & (1<<UDRE0)) );// Wait for empty transmit buffer
	UDR0 = data; // Put data into buffer, sends the data
	return 0;
}

int USART_Receive( void ){ // Definert som unsigned char i node 1??

	while ( !(UCSR0A & (1<<RXC0)) );// Wait for data to be received
	return UDR0; // Get and return received data from buffer
}
