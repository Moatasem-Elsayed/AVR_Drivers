/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: SPI peripheral
*******************************************************/

#ifndef MCAL_06_SPI_SPI_H_
#define MCAL_06_SPI_SPI_H_

#include "../MCAL_REGISTERS/Mem_Map32.h"
#include "Std_Types.h"
#include "Utils.h"
#include <avr/delay.h>
/****************** Configuration Menu *******************/

#define DIV_FACTOR  		FOSC_DIV8
#define SPI_MODE			3
#define DATA_ORDER			MSB

/********************************************************/
//data ordered to send and receive
#define LSB				1
#define MSB				0
//Relationship Between SCK and the Oscillator Frequency
#define FOSC_DIV4		0
#define FOSC_DIV16		1
#define FOSC_DIV64		2
#define FOSC_DIV128 	3
#define FOSC_DIV2 		4
#define FOSC_DIV8		5
#define FOSC_DIV32		6
#define FOSC_DIV64_		7
#define SLAVE_MODE      8


void SPI_Init();							/* SPI initialize function */
void SPI_Write(uint8);						/* SPI write data function */
uint8 SPI_Read();

#endif /* MCAL_06_SPI_SPI_H_ */
