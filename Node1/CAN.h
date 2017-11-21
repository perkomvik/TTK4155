/*
 * CAN.h
 *
 * Created: 18.10.2017 16:45:37
 *  Author: mariuesk
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "utilities.h"
#include "MCP2515.h"

typedef struct CAN_msg{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
}CAN_msg;

typedef enum tag_CAN_msg_id{
	PONG_START = 0,
	PONG_STOP = 1,
	PONG_INSTR = 2
}CAN_msg_id;

static volatile uint8_t CAN_int_flag = 0;

void CAN_init(uint8_t mode);
void CAN_message_send(CAN_msg* msg);
uint8_t CAN_receive(CAN_msg* msg);
void CAN_print(CAN_msg* msg);
ISR(INT2_vect);


#endif /* CAN_H_ */