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
}

void OLED_home(void){ // Puts cursor at upper left corner of OLED
	//OLED cursor
	*OLED_C = 0xb0;
	*OLED_C = 0x10;
	*OLED_C = 0x00;
	//SRAM buffer cursor
	cursor = 0;
}

void OLED_goto_line(OLED_line line){ // Puts cursor at start of selected line
	*OLED_C = 0xb0 + line;
	*OLED_C = 0x10;
	*OLED_C = 0x00;

	cursor = N_OLED_LINE_BYTES*line;
}

void OLED_clear_line(OLED_line line){ // "Clears" selected line by filling with whitespace
	cursor = N_OLED_LINE_BYTES*line;
	uint8_t volatile* sram_pointer = (uint8_t *) (SRAM_MEM_ADR);
	for (uint8_t b = 0; b < N_OLED_LINE_BYTES; b++){
		sram_pointer[cursor] = ' '; // whitespace
		cursor++;
	}

}

void OLED_clear(void){ // "Clears" buffer by filling with whitespace
	for (OLED_line line = LINE_1; line < N_OLED_LINES; line++){
		OLED_clear_line(line);
	}
	OLED_home();
}

void OLED_pos(uint8_t row, uint8_t column){ // Puts cursor at selected coordinate
	cursor = (N_OLED_LINE_BYTES*row) + column;
}

void OLED_fill(void){ // Fills the display by turning on every pixel
	uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
	for (OLED_line line = 0; line < N_OLED_LINES; line++){
		OLED_goto_line(line);
		for (uint8_t b = 0; b < N_OLED_LINE_BYTES; b++){
			sram_pointer[cursor] = FULLWHITE;
			cursor++;
		}
	}
}

void OLED_load_sym(char symbol){ // Loads a single char from SRAM buffer to OLED
	if (symbol >= 31){
		for (uint8_t b = 0; b < 8; b++){
			*OLED_D = pgm_read_byte(&font8[symbol-31][b]);
		}	
	}
}

void OLED_store_str(char* string){ // Stores string in SRAM buffer
	uint8_t str_index = 0;
	uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
	while (string[str_index] != '\0'){
		if (cursor < N_OLED_BYTES){
			sram_pointer[cursor] = string[str_index];
		}
		cursor++;
		str_index++;
	}
}

void OLED_store_sym(char symbol){ // Stores symbol in SRAM buffer
	if (symbol >= 31){
		uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
		sram_pointer[cursor] = symbol;
		cursor++;
	}
}

void OLED_refresh(void){ // Prints the full screen from SRAM to OLED
	OLED_home();
	uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
	char symbol;
	OLED_line line = LINE_1;
	for (int b = 0; b < N_OLED_BYTES; b++){
		symbol = sram_pointer[b];
		if (!(b % N_OLED_LINE_BYTES) && b != 0){
			line++;
			OLED_goto_line(line);		
		}
		OLED_load_sym(symbol);
	}
	OLED_home();
}

uint8_t get_cursor(void){ // Get current cursor position
	return cursor;
}

void OLED_print_buffer(void){ // Prints what is currently in the SRAM buffer to terminal.
	uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
	char symbol;
	OLED_line line = LINE_1;
	for (int b = 0; b < N_OLED_BYTES; b++){
		symbol = sram_pointer[b];
		if (!(b % N_OLED_LINES) && b != 0){
			line++;
			OLED_goto_line(line);
			printf("\n");
		}
		printf("%c", symbol);
	}
}


void OLED_store_menu(char* string){ // Stores chosen menu in SRAM buffer
	OLED_home();
	uint8_t str_index = 0;
	uint8_t volatile* sram_pointer = (uint8_t *)(SRAM_MEM_ADR);
	while (string[str_index] != '\0'){
		if (cursor < N_OLED_BYTES){
			if(string[str_index] == '¤'){ // ¤ is used as key for a line of whitespace to save data memory
				OLED_clear_line(cursor/N_OLED_LINE_BYTES); //Updates cursor in function
				str_index++;
			}else{
				sram_pointer[cursor] = string[str_index];
				str_index++;
				cursor++;
			}	
		}
	}
}

void OLED_loading_screen(void){
	uint8_t dot_step = 1;
	OLED_clear();
	OLED_goto_line(LINE_4);
	OLED_store_str("    LOADING     ");
	for(uint8_t i = 0; i < 3; i+=dot_step){
		OLED_pos(LINE_4,11+i);
		if(i == 0){
			OLED_store_sym('.');
		} else{
			OLED_store_sym('.');
			OLED_pos(LINE_4,12+i-dot_step);
		}
		OLED_refresh();
		_delay_ms(600);
	}
}

void OLED_loading_screen_long(void){
	uint8_t dot_step = 1;
	OLED_clear();
	OLED_goto_line(LINE_4);
	OLED_store_str("    LOADING     ");
	for(uint8_t i = 0; i < 3; i+=dot_step){
		OLED_pos(LINE_4,11+i);
		if(i == 0){
			OLED_store_sym('.');
			} else{
			OLED_store_sym('.');
			OLED_pos(LINE_4,12+i-dot_step);
		}
		OLED_refresh();
		_delay_ms(1200);
	}
}

void OLED_game_over_screen(void){
	OLED_clear();
	OLED_goto_line(LINE_4);
	OLED_store_str("    GAME OVER   ");
	OLED_refresh();
	_delay_ms(2000);
}
