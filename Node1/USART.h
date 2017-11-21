#ifndef USART_H_
#define USART_H_

#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "utilities.h"

void USART_Init(void);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_test(void);


#endif /* USART_H_ */

