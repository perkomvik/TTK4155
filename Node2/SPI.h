/*
 * SPI.h
 *
 * Created: 25.10.2017 12:36:57
 *  Author: mariuesk
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "utilities.h"
char SPI_Read(void);
void SPI_Send(char cData);
void SPI_MasterInit(void);




#endif /* SPI_H_ */