/*
 * ADC.h
 *
 * Created: 01.11.2017 11:17:30
 *  Author: mariuesk
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "utilities.h"

typedef enum tag_ADC_channel {
	CHANNEL_0 = 0,
	CHANNEL_1 = 1
} ADC_channel;

void ADC_init(void);
uint16_t ADC_read(void);
uint16_t ADC_read_channel(ADC_channel channel);


#endif /* ADC_H_ */