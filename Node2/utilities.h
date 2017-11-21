/*
 * Utilities.h
 *
 * Created: 06.09.2017 11:41:36
 *  Author: mariuesk
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_


#define UP -1
#define DOWN 1
#define ARROW 127
#define FULLWHITE 31

#define F_CPU 16000000UL // 16 MHz
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define bit_get(reg, bit) ((reg) & (bit))
#define CHECKBIT(reg,bit) (reg & (1<<bit))
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )


#endif /* UTILITIES_H_ */
