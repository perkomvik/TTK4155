/*
 * CAN.c
 *
 * Created: 18.10.2017 16:45:25
 *  Author: mariuesk
 */ 

#include "CAN.h"

void CAN_init(uint8_t mode){
	mcp2515_init(mode);

	cli(); // Disable global interrupts

	set_bit(EIMSK,INT2); // Enable interrupt 2
	set_bit(EIFR,INTF2); // Clear intrerrupt flag 2

	sei(); // Enable global interrupts
	
}
void CAN_message_send(CAN_message* msg){

	mcp2515_write(MCP_TXB0SIDH, (msg->id) >> 3); // Set message ID high bits
	mcp2515_write(MCP_TXB0SIDL, (msg->id) << 5); // Set message ID low bits 
	mcp2515_write(MCP_TXB0DLC, (msg->length)); // Set data length
	
	for (uint8_t i = 0; i < msg->length; i++){
		mcp2515_write(MCP_TXB0D0+i, msg->data[i]); // Set data bits
	}
	mcp2515_request_to_send(MCP_RTS_TX0); // Sends data to TX0 buffer 
}

uint8_t CAN_receive(CAN_message* msg){
	if (CAN_int_flag){
		uint8_t IDHI = mcp2515_read(MCP_RXB0SIDH); // Read message ID high bits
		uint8_t IDLO = mcp2515_read(MCP_RXB0SIDL); // Read message ID low bits
		msg->id = (IDHI << 3| IDLO >> 5); // Combine to complete message ID
		
		uint8_t length = mcp2515_read(MCP_RXB0DLC); // Read message data length
		msg->length = length;
	
	
		for (uint8_t i = 0; i < msg->length; i++){
			msg->data[i] = mcp2515_read(MCP_RXB0D0+i);  // Read data bits
		}
		mcp2515_bit_modify(MCP_CANINTF,0x01,0x00); // Reset interrupt flag
		CAN_int_flag = 0;
		return 1;
	}
	return 0;
}

void CAN_print(CAN_message* msg){
	printf("CAN msg ID: %d \n", msg->id);
	printf("CAN msg length: %d \n", msg->length);
	printf("CAN msg data: ");
	for (int i = 0; i < msg->length; i++){
		printf("%d \t",msg->data[i]);
	}
	printf("\n");
}

ISR(INT2_vect){
	CAN_int_flag = 1;
}
