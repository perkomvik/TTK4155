/*
 * Usart_Driver.c
 *
 * Created: 18.10.2017 18:39:31
 *  Author: mariuesk
 */ 
#include <avr/io.h>
#include<stdio.h>
#include "Usart_Driver.h"


void USART_Init(void){
	//int ubrr = 11; // Usart_init parameter
	/* Set baud rate */
	uint16_t ubrr = F_CPU / 16 / BAUD - 1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	fdevopen(USART_Transmit, USART_Receive);
	
}

int USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
	return 0;
}

int USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}