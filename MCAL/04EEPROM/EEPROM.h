
/*****************************************************
*Author :	Moatasem
*Date	:   12/10/2018
*Version: 	v02
*Brief	: 	Internal EEPROM
*******************************************************/
#ifndef _EPPROM_H
#define _EEPROM_H_

#include "Utils.h"
#include "Std_Types.h"
#include  "../../MCAL_REGISTERS/Mem_Map32.h"



void EEPROM_write(uint16 uiAddress, uint8 ucData);
uint8 EEPROM_read(uint16 Address);
/***tasks********/
uint32 EEPROM_READ_4byte(uint16 Address);
void EEPROM_WRITE_4byte(uint16 Address,uint32 data);

#define EEPROM_INTERRUPT_ENABLE()	WRITE_BIT(EECR,EERIE,HIGH)
#endif
