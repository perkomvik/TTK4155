#include "Usart_Driver.h"

void USART_Init(void){
//int ubrr = 11; // Usart_init parameter
/* Set baud rate */

uint16_t ubrr = 4915200 / 16 / 9600 - 1;
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // |(1<<USBS0) fjernet 2stop bit
clear_bit(UCSR0C, 0);
fdevopen(USART_Transmit, USART_Receive);
//stdin = fdevopen(NULL, USART_Receive);
//stdout = fdevopen(USART_Transmit, NULL);
}

void USART_Transmit( unsigned char data )
{	
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_test(void){
	char hei[10];
	scanf("%s",hei);
	printf("%s\n",hei);
}
