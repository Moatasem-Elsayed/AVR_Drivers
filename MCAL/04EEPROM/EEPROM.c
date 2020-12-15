/*****************************************************
*Author :	Moatasem
*Date	:   12/10/2018
*Version: 	v02
*Brief	: 	Internal EEPROM
*******************************************************/
#include "EEPROM.h"
volatile uint8 data;
uint8 EEPROM_read(uint16 Address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = Address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_write(uint16 Address, uint8 ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = Address;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}
uint32 EEPROM_READ_4byte(uint16 Address)
{
	uint8 val=0;
	uint32 result=0;
	for(uint8 i=0;i<4;i++)
	{
		val=EEPROM_read(Address+i);
		result=result+((uint32)val<<i*8);

	}
	return result;
}
void EEPROM_WRITE_4byte(uint16 Address,uint32 data)
{
	for(uint8 i=0;i<4;i++)
	{
	EEPROM_write(Address+i,(uint8)(data>>(i*8)));
	}
	
}
ISR(EE_RDY_vect)
{
	EEDR=data;
	EEAR=0x01;
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);


}
