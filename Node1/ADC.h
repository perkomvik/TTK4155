/*
 * ADC.h
 *
 * Created: 13.09.2017 12:11:13
 *  Author: perkom
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "utilities.h"

#define ADC_MEM_ADR 0x1400

typedef enum tag_ADC_channel {
	CHANNEL_1 = 1,
	CHANNEL_2 = 2,
	CHANNEL_3 = 3,
	CHANNEL_4 = 4
} ADC_channel;

uint8_t ADC_read(ADC_channel channel);
	
#endif /* ADC_H_ */