/*
 * Usart_Driver.h
 *
 * Created: 18.10.2017 18:39:44
 *  Author: mariuesk
 */ 


#ifndef USART_H_
#define USART_H_

#include "utilities.h"
void USART_Init(void);
int USART_Transmit(unsigned char data);
int USART_Receive( void );

#endif /* USART_H_ */
