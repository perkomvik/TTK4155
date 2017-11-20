/*
 * SPI.h
 *
 * Created: 04.10.2017 13:02:58
 *  Author: andersgd
 */ 



#ifndef SPI_H_
#define SPI_H_

#include "Utilities.h"

char SPI_Read(void);
void SPI_Send(char cData);
void SPI_MasterInit(void);


#endif /* SPI_H_ */