/*
 * MCP2515.c
 *
 * Created: 04.10.2017 16:46:54
 *  Author: andersgd
 */ 
#include "MCP2515.h"

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	SPI_Send(MCP_READ); // Send read command
	SPI_Send(address); // Send address
	result = SPI_Read(); //Read result
	PORTB |= (1<<PB4); //Deselect CAN - controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t cData){
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	SPI_Send(MCP_WRITE); // Send write command
	SPI_Send(address); // Send address
	SPI_Send(cData);
	PORTB |= (1<<PB4); //Deselect CAN - controller
}

void mcp2515_reset(){
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	
	SPI_Send(MCP_RESET);
	
	mcp2515_bit_modify(MCP_CANCTRL, 0x80,0x80); //force config mode
	
	PORTB |= (1<<PB4); //Deselect CAN - controller
	_delay_us(10);
}

void mcp2515_set_mode(uint8_t mode){
	mcp2515_write(MCP_CANCTRL, mode);
}

void mcp2515_request_to_send(uint8_t buffer){
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	SPI_Send(buffer); // use 0x81 MCP_RTS_TX0
	PORTB |= (1<<PB4); //Deselect CAN - controller
}

uint8_t mcp2515_read_status(){
	uint8_t status;
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	SPI_Send(MCP_READ_STATUS);
	status = SPI_Read();
	PORTB |= (1<<PB4); //Deselect CAN - controller
	return status;
}

void mcp2515_bit_modify(uint8_t regist, uint8_t mask, uint8_t cData){
	PORTB &= ~(1<<PB4); //SelectCAN-controller Chip select
	SPI_Send(MCP_BITMOD);
	SPI_Send(regist);
	SPI_Send(mask);
	SPI_Send(cData);
	PORTB |= (1<<PB4); //Deselect CAN - controller
	
}

uint8_t mcp2515_init(uint8_t mode){
	uint8_t theValue;
	SPI_MasterInit(); //Initialize SPI
	mcp2515_reset(); // Send reset-command
	//Self-test
	theValue = mcp2515_read(MCP_CANSTAT);
	if((theValue& MODE_MASK)  != MODE_CONFIG) {
		//printf("MCP2515 is NOT in configuration mode after reset! canstat: 0x%02x\n", theValue);
		return 1;
	} 
	else{
		//printf("MCP2515 is  in configuration mode after reset! canstat: 0x%02x\n", theValue);
	}
	
	mcp2515_set_mode(mode);
	theValue = mcp2515_read(MCP_CANSTAT);
	int mode_bits = (theValue & MODE_MASK);
	if(mode_bits != mode){
		printf("MCP2515 is NOT in correct mode after reset! Its config bits are %x\n", mode_bits);
		return 1;
	}
	mcp2515_write(MCP_CANINTE, MCP_RX_INT);// enable interrups
	return 0;
}
