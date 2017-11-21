/*
 * Usart_Driver.h
 *
 * Created: 18.10.2017 18:39:44
 *  Author: mariuesk
 */ 


#ifndef USART_H_
#define USART_H_

#include "utilities.h"
void USART_init(void);
int USART_transmit(unsigned char data);
int USART_receive( void );

#endif /* USART_H_ */
