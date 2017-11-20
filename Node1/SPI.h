/*
 * SPI.h
 *
 * Created: 04.10.2017 13:02:58
 *  Author: andersgd
 */ 



#ifndef SPI_H_
#define SPI_H_

#include "utilities.h"

char SPI_read(void);
void SPI_send(char cData);
void SPI_master_init(void);


#endif /* SPI_H_ */