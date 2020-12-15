#include "RTC.h"

int second,minute,hour,day,date,month,year;

void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM2)
{
	_hour |= AMPM2;
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(0);								/* Write on 0 location for second value */
	I2C_Write(_second);							/* Write second value on 00 location */
	I2C_Write(_minute);							/* Write minute value on 01 location */
	I2C_Write(_hour);							/* Write hour value on 02 location */
	I2C_Stop();									/* Stop I2C communication */
}

void RTC_Calendar_Write(char _day, char _date, char _month, char _year)	/* function for calendar */
{
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(3);								/* Write on 3 location for day value */
	I2C_Write(_day);							/* Write day value on 03 location */
	I2C_Write(_date);							/* Write date value on 04 location */
	I2C_Write(_month);							/* Write month value on 05 location */
	I2C_Write(_year);							/* Write year value on 06 location */
	I2C_Stop();									/* Stop I2C communication */
}

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);				/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);					/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);		/* Repeated start with device read address */

	second = I2C_Read_Ack();						/* Read second */
	minute = I2C_Read_Ack();						/* Read minute */
	hour = I2C_Read_Nack();							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	day = I2C_Read_Ack();							/* Read day */
	date = I2C_Read_Ack();							/* Read date */
	month = I2C_Read_Ack();							/* Read month */
	year = I2C_Read_Nack();							/* Read the year with Nack */
	I2C_Stop();										/* Stop i2C communication */
}
