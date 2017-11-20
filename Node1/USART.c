#include "USART.h"

void USART_Init(void){

/* Set baud rate */
uint16_t ubrr = F_CPU / 16 / 9600 - 1;
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter 

UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // Set frame format: 8data, 2stop bit
clear_bit(UCSR0C, 0); // Clock polarity: set to zero when using asynchronous
fdevopen(USART_Transmit, USART_Receive);
}

void USART_Transmit( unsigned char data )
{	
	while ( !( UCSR0A & (1<<UDRE0)) );// Wait for empty transmit buffer
	UDR0 = data; // Put data into buffer, sends the data
}

unsigned char USART_Receive( void )
{
	while ( !(UCSR0A & (1<<RXC0)) );// Wait for data to be received
	return UDR0; // Get and return received data from buffer
}

void USART_test(void){
	char hei[10];
	scanf("%s",hei);
	printf("%s\n",hei);
}