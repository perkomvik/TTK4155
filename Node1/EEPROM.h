/*
 * EEPROM.h
 *
 * Created: 20.11.2017 18:25:04
 *  Author: mariuesk
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "utilities.h"
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);


#endif /* EEPROM_H_ */