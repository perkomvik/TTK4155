/*
 * OLED.h
 *
 * Created: 20.09.2017 12:19:31
 *  Author: perkom
 */ 

//#ifndef OLED_H_
#ifndef OLED_H_
#define OLED_H_

#include "utilities.h"
#define ARROW 127
#define FULLWHITE 31
#define N_OLED_LINES 8
#define N_OLED_LINE_BYTES 16
#define N_OLED_BYTES 128
#define OLED_C_MEM_ADR 0x1000
#define OLED_D_MEM_ADR 0x1200
#define SRAM_MEM_ADR 0x1800

#define OLED_C ((volatile char*) (OLED_C_MEM_ADR))
#define OLED_D ((volatile char*) (OLED_D_MEM_ADR))

typedef enum tag_OLED_line{
	LINE_1 = 0,
	LINE_2 = 1,
	LINE_3 = 2,
	LINE_4 = 3,
	LINE_5 = 4,
	LINE_6 = 5,
	LINE_7 = 6,
	LINE_8 = 7
}OLED_line;


static int cursor = 0; // cursor represents OLED cursor for our SRAM

void OLED_init(void); // PDF:“OLED LY190-128064" section 9.4
void OLED_home(void);
void OLED_goto_line(OLED_line line);
void OLED_clear_line(OLED_line line);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_fill(void);
void OLED_clear(void);
void OLED_load_sym(char symbol);
void OLED_store_sym(char symbol);
void OLED_store_str(char* string);
void OLED_print_buffer(void);
void OLED_refresh(void);
void OLED_store_menu(char* string);
void OLED_loading_screen(void);
void OLED_loading_screen_long(void);
void OLED_game_over_screen(void);
void OLED_snek(void);
uint8_t get_cursor(void);



#endif /* OLED_H_ */