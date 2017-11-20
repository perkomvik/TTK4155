#ifndef Usart_Driver_H_
#define Usart_Driver_H_

#define F_CPU 4915200
#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "Utilities.h"
#include <avr/io.h>
#include <util/delay.h>
//#include<time.h>
#include<stdio.h>
void USART_Init(void);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_test(void);


#endif /* SPI_H_ */

