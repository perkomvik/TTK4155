/*
 * OLED.c
 *
 * Created: 20.09.2017 12:19:13
 *  Author: perkom
 */ 
#include "OLED.h"
#include "fonts.h"
//static int CURSOR = 0;
#define OLED_C ((volatile char*) 0x1000)
#define OLED_D ((volatile char*) 0x1200)
//#define SRAM_P ((volatile char*) 0x1800)
void write_c(uint8_t hex){
	*OLED_C = hex;
}

void OLED_init(){
	write_c(0xae);        //display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common  output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x0a);
	write_c(0xd9);        //set  pre-charge  period
	write_c(0x21);	     //only for horizontal and vertical mode
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x02);
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        //out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	
		  
		  
	//SRAM INITIALIZE
	for (int i = 0; i < 128; i++){
		uint16_t volatile* sram_pointer = (uint16_t *) (0x1800 + i);
		*sram_pointer = ' ';
	}
	OLED_refresh();
	}

void OLED_reset(){
	
	return;
}

void OLED_home(){
	// go home
	*OLED_C = 0xb0;
	*OLED_C = 0x10;
	*OLED_C = 0x00;
	cursor = 0;
	
}

void OLED_goto_line(int line){
	*OLED_C = 0xb0 + line;
	*OLED_C = 0x10;
	*OLED_C = 0x00;
	cursor = 16*line;
}

void OLED_clear_line(int line){
	cursor = 16*line;
	for (int i = 0; i < 16; i++){
		uint8_t volatile* sram_pointer = (uint8_t *) (0x1800 + cursor);
		*sram_pointer = ' '; // whitespace
		cursor++;
	}

}

void OLED_clear(){
	for (int i = 0; i < 8; i++){
		OLED_clear_line(i);
	}
	cursor = 0;
}

void OLED_pos(uint8_t row, uint8_t column){
	cursor = (16*row) + column;
}

void OLED_fill(){
	for (int line = 0; line < 8; line++){
		OLED_goto_line(line);
		for (int k = 0; k < 16; k++){
			uint8_t volatile* sram_pointer = (uint8_t *)(0x1800 + cursor);
			*sram_pointer = FULLWHITE;
			cursor++;
		}
	}
}

void OLED_set_brightness(int lvl){
	
	return;
}

void print_OLED_symbol_from_sram(char symbol){
	if (symbol >= 31){
		for (int i = 0; i < 8; i++){
			*OLED_D = pgm_read_byte(&font8[symbol-31][i]);
		}	
	}
}
void print_OLED_string(char* string){
	int index = 0;
	while (string[index] != '\0'){
		if (cursor < 128){
			uint8_t volatile* sram_pointer = (uint8_t *)(0x1800 + cursor);
			
			*sram_pointer = string[index];
		}
		cursor++;
		index++;
	}
}

void print_OLED_symbol(char symbol){
	if (symbol >= 31){
		uint8_t volatile* sram_pointer = (uint8_t *)(0x1800 + cursor);
		*sram_pointer = symbol;
		cursor++;
	}
}

void OLED_refresh(){
	OLED_home();
	char b;
	int line = 0;
	for (int i = 0; i < 128; i++){
		uint8_t volatile* sram_pointer = (uint8_t *)(0x1800 + i);
		b = *sram_pointer;
		//printf("%c", b);
		if (!(i % 16) && i != 0){
			line++;
			OLED_goto_line(line);
			//printf("\n");
		}
		print_OLED_symbol_from_sram(b);
	}
	OLED_home();
}

int get_cursor(){
	return cursor;
}

void print_sram(){
	OLED_home();
	int b = 0;
	int line = 0;
	for (int i = 0; i < 128; i++){
		uint8_t volatile* sram_pointer = (uint8_t *)(0x1800 + i);
		b = *sram_pointer;
		if (!(i % 16) && i != 0){
			line++;
			OLED_goto_line(line);
			printf("\n");
		}
		printf("%c", b);
	}
	OLED_home();
}

