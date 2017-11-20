/*
 * Utilities.h
 *
 * Created: 06.09.2017 11:41:36
 *  Author: mariuesk
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_




#define F_CPU 4915200
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdio.h> //NEEDed?
#include<stdlib.h> //NEEDED?
#define bit_get(reg, bit) ((reg) & (bit))
//#define CHECKBIT(reg,bit) (reg & (1<<bit))
#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )


#endif /* UTILITIES_H_ */