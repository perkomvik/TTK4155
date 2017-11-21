/*
 * MCP2515.c
 *
 * Created: 25.10.2017 13:11:22
 *  Author: mariuesk
 */ 

#include "MCP2515.h"
#include "SPI.h"

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1<<PB7); // Chip select CAN-controller

	SPI_Send(MCP_READ); // Send read command
	SPI_Send(address); // Send address
	result = SPI_Read(); // Read result

	PORTB |= (1<<PB7); // Deselect CAN-controller
	return result;
}

void mcp2515_write(uint8_t address, uint8_t cData){
	PORTB &= ~(1<<PB7); // Chip select CAN-controller

	SPI_Send(MCP_WRITE); // Send write command
	SPI_Send(address); // Send address
	SPI_Send(cData); // Send data

	PORTB |= (1<<PB7); //Deselect CAN-controller
}

void mcp2515_reset(){
	PORTB &= ~(1<<PB7); // Chip select CAN-controller
	
	SPI_Send(MCP_RESET); // Set registers to default state
	mcp2515_bit_modify(MCP_CANCTRL, MODE_CONFIG,MODE_CONFIG); // Force the CAN-controller to enter configuration mode
	
	PORTB |= (1<<PB7); // Deselect CAN-controller
	_delay_us(10);
}

void mcp2515_set_mode(uint8_t mode){
	mcp2515_write(MCP_CANCTRL, mode); // Write mode to MCP_CANCTRL register
}

void mcp2515_request_to_send(uint8_t buffer){
	PORTB &= ~(1<<PB7); // Chip select CAN-controller
	SPI_Send(buffer); // Send to chosen buffer. Generally use MCP_RTS_TX0
	PORTB |= (1<<PB7); //Deselect CAN-controller
}

uint8_t mcp2515_read_status(){
	uint8_t status;
	PORTB &= ~(1<<PB7); // Chip select CAN-controller
	SPI_Send(MCP_READ_STATUS); // Read the status
	status = SPI_Read();
	PORTB |= (1<<PB7); //Deselect CAN - controller
	return status;
}

void mcp2515_bit_modify(uint8_t regist, uint8_t mask, uint8_t cData){
	PORTB &= ~(1<<PB7); //SelectCAN-controller Chip select

	SPI_send(MCP_BITMOD); // Ready bit modify instruction
	SPI_send(regist); // Choose register
	SPI_send(mask); // Send bit mask
	SPI_send(cData); // Modify the bits to match cData

	PORTB |= (1<<PB7); //Deselect CAN - controller
}

uint8_t mcp2515_init(uint8_t mode){
	uint8_t mode_value;
	SPI_MasterInit(); // Initialize SPI
	mcp2515_reset(); // Send reset-command
	
	mode_value = mcp2515_read(MCP_CANSTAT); // Read current mode
	if((mode_value& MODE_MASK)  != MODE_CONFIG) {
		return 1;
	}
	else{
	}

	mcp2515_set_mode(mode);
	mode_value = mcp2515_read(MCP_CANSTAT);
	int mode_bits = (mode_value & MODE_MASK);
	if(mode_bits != mode){ // Check if chosen mode is the same as current mode
		return 1;
	}
	mcp2515_write(MCP_CANINTE, MCP_RX_INT); // Enable interrupt
	return 0;
}
