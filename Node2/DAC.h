/*
 * DAC.h
 *
 * Created: 08.11.2017 12:00:56
 *  Author: mariuesk
 */ 


#ifndef DAC_H_
#define DAC_H_

#include "Utilities.h"
#include "TWI_Master.h"
void DAC_init();
void DAC_send(uint8_t data);


#endif /* DAC_H_ */