/*
 * Usart_Driver.h
 *
 * Created: 18.10.2017 18:39:44
 *  Author: mariuesk
 */ 


#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include "Utilities.h"
void USART_Init(void);
int USART_Transmit(unsigned char data);
int USART_Receive( void );

#endif /* USART_DRIVER_H_ */
