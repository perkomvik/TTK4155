/*
 * OLED.c
 *
 * Created: 20.09.2017 12:19:13
 *  Author: perkom
 */ 
#include "OLED.h"
#include "fonts.h"


//#define SRAM_P ((volatile char*) 0x1800)


void OLED_init(void){
	*OLED_C = 0xae;        // Display  off
	*OLED_C = 0xa1;        // Segment  remap
	*OLED_C = 0xda;        // Common  pads  hardware:  alternative
	*OLED_C = 0x12;
	*OLED_C = 0xc8;		   // Common  output scan direction:com63~com0
	*OLED_C = 0xa8;        // Multiplex  ration  mode:63
	*OLED_C = 0x3f;
	*OLED_C = 0xd5;        // Display divide ratio/osc. freq. mode
	*OLED_C = 0x80;
	*OLED_C = 0x81;        // Contrast  control
	*OLED_C = 0x0a;
	*OLED_C = 0xd9;        // Set  pre-charge  period
	*OLED_C = 0x21;	       // Only for horizontal and vertical mode
	*OLED_C = 0x20;        // Set  Memory  Addressing  Mode
	*OLED_C = 0x02;
	*OLED_C = 0xdb;        // VCOM  deselect  level  mode
	*OLED_C = 0x30;
	*OLED_C = 0xad;        // Master  configuration
	*OLED_C = 0x00;
	*OLED_C = 0xa4;        // Out  follows  RAM  content
	*OLED_C = 0xa6;        // Set  normal  display
	*OLED_C = 0xaf;        // Display  on
	
	//SRAM BUFFER INITIALIZE, needed?
	uint16_t volatile* sram_pointer;
	for (int b = 0; b < N_OLED_BYTES; b++){
		sram_pointer = (uint16_t *) (SRAM_MEM_ADR + b);
		*sram_pointer = ' ';
	}
}

void OLED_home(void){ // Puts cursor at upper left corner of OLED
	*OLED_C = 0xb0;
	*OLED_C = 0x10;
	*OLED_C = 0x00;
	cursor = 0;
}

void OLED_goto_line(OLED_line line){ // Puts cursor at start of selected line
	*OLED_C = 0xb0 + line;
	*OLED_C = 0x10;
	*OLED_C = 0x00;
	cursor = N_OLED_LINE_BYTES*line;
}

void OLED_clear_line(OLED_line line){ // Clears selected line by filling with whitespace
	cursor = N_OLED_LINE_BYTES*line;
	uint8_t volatile* sram_pointer;
	for (uint8_t b = 0; b < N_OLED_LINE_BYTES; b++){
		sram_pointer = (uint8_t *) (SRAM_MEM_ADR + cursor);
		*sram_pointer = ' '; // whitespace
		cursor++;
	}

}

void OLED_clear(void){ // Clears display by filling with whitespace
	for (OLED_line line = LINE_1; line < N_OLED_LINES; line++){
		OLED_clear_line(line);
	}
	OLED_home();
}

void OLED_pos(uint8_t row, uint8_t column){ // Puts cursor at selected coordinate
	cursor = (N_OLED_LINE_BYTES*row) + column;
}

void OLED_fill(void){ // Fills the display by turning on every pixel
	uint8_t volatile* sram_pointer;
	for (OLED_line line = 0; line < N_OLED_LINES; line++){
		OLED_goto_line(line);
		for (uint8_t b = 0; b < N_OLED_LINE_BYTES; b++){
			sram_pointer = (uint8_t *)(SRAM_MEM_ADR + cursor);
			*sram_pointer = FULLWHITE;
			cursor++;
		}
	}
}

void OLED_load_sym(char symbol){ // Print symbol to OLED
	if (symbol >= 31){
		for (uint8_t b = 0; b < 8; b++){
			*OLED_D = pgm_read_byte(&font8[symbol-31][b]);
		}	
	}
}

void OLED_store_str(char* string){ // Stores string in SRAM to be printed to OLED
	uint8_t str_index = 0;
	uint8_t volatile* sram_pointer;
	while (string[str_index] != '\0'){
		if (cursor < N_OLED_BYTES){
			sram_pointer = (uint8_t *)(SRAM_MEM_ADR + cursor);
			*sram_pointer = string[str_index];
		}
		cursor++;
		str_index++;
	}
}

void OLED_store_sym(char symbol){ // Stores symbol in SRAM to be printed to OLED
	if (symbol >= 31){
		uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR + cursor);
		*sram_pointer = symbol;
		cursor++;
	}
}

void OLED_refresh(void){ // Prints the full screen from SRAM to OLED
	OLED_home();
	uint8_t volatile* sram_pointer;
	char symbol;
	OLED_line line = LINE_1;
	for (int b = 0; b < N_OLED_BYTES; b++){
		sram_pointer = (uint8_t *)(SRAM_MEM_ADR + b);
		symbol = *sram_pointer;
		//printf("%c", b);
		if (!(b % N_OLED_LINE_BYTES) && b != 0){
			line++;
			OLED_goto_line(line);
			//printf("\n");
		}
		OLED_load_sym(symbol);
	}
	OLED_home();
}

uint8_t get_cursor(void){ // Get current cursor position
	return cursor;
}

void OLED_print(void){ // Prints what is currently on the OLED.
	OLED_home();
	char symbol;
	OLED_line line = LINE_1;
	for (int b = 0; b < N_OLED_BYTES; b++){
		uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR + b);
		symbol = *sram_pointer;
		if (!(b % N_OLED_LINES) && b != 0){
			line++;
			OLED_goto_line(line);
			printf("\n");
		}
		printf("%c", symbol);
	}
	OLED_home();
}


void OLED_store_menu(char* string){ // Stores chosen menu in SRAM to be printed to OLED 
	cursor = 0;
	uint8_t str_index = 0;
	uint8_t volatile* sram_pointer;
	while (string[str_index] != '\0'){
		if (cursor < N_OLED_BYTES){
			sram_pointer = (uint8_t *)(SRAM_MEM_ADR + cursor);
			if(string[str_index] == '¤'){
				printf("clear line: %d\n",cursor/N_OLED_LINE_BYTES);
				OLED_clear_line(cursor/N_OLED_LINE_BYTES);
				str_index++;
			}else{
				*sram_pointer = string[str_index];
				str_index++;
				cursor++;
			}	
		}
	}
}