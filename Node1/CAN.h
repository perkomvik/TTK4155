/*
 * CAN.h
 *
 * Created: 18.10.2017 16:45:37
 *  Author: mariuesk
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "Utilities.h"
#include "MCP2515.h"

typedef struct CAN_message{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
}CAN_message;

static volatile uint8_t CAN_int_flag = 0;
void CAN_init(uint8_t mode);
void CAN_message_send(CAN_message* msg);
uint8_t CAN_receive(CAN_message* msg);
void CAN_print(CAN_message* msg);
ISR(INT2_vect);


#endif /* CAN_H_ */