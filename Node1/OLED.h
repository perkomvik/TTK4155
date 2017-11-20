/*
 * OLED.h
 *
 * Created: 20.09.2017 12:19:31
 *  Author: perkom
 */ 



//#ifndef OLED_H_
#ifndef OLED_H_
#define OLED_H_
#include "Utilities.h"
static int cursor;
void OLED_init(void); // PDF:“OLED LY190-128064" section 9.4
void OLED_reset();
void OLED_home();
void OLED_goto_line(int line);
void OLED_clear_line(int line);
void OLED_pos(uint8_t row, uint8_t column);
void OLED_print(char* a);
void OLED_set_brightness(int lvl);
void OLED_set_memes();
void OLED_fill();
void OLED_clear();
void write_c(uint8_t hex);
void print_OLED_symbol_from_sram(char symbol);
void print_OLED_symbol(char symbol);
void print_OLED_string(char* string);
void print_sram();
void OLED_refresh();
int get_cursor();


#endif /* OLED_H_ */