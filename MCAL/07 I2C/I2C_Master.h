/*
 * I2C_Master_H_file.h
 * www.electronicwings.com
 */ 

#ifndef I2C_MASTER_H_					/* Define library H file if not defined */
#define I2C_MASTER_H_
#include "Std_Types.h"
#include "Utils.h"
#include "../MCAL_REGISTERS/Mem_Map32.h"
#include <math.h>								/* Include math function */

#define SCL_CLK 100000L							/* Define SCL clock frequency */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */

void   I2C_Init();								/* I2C initialize function */
uint8  I2C_Start(uint8 write_address);			/* I2C start function */
uint8  I2C_Repeated_Start(uint8 read_address);	/* I2C repeated start function */
void   I2C_Stop();								/* I2C stop function */
void   I2C_Start_Wait(uint8 write_address);		/* I2C start wait function */
uint8  I2C_Write(uint8 data);					/* I2C write function */
uint8  I2C_Read_Ack();							/* I2C read ack function */
uint8  I2C_Read_Nack();							/* I2C read nack function */


#endif											/* I2C_MASTER_H_FILE_H_ */
