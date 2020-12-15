/*
 * RTC.h
 *
 *  Created on: Nov 21, 2020
 *      Author: engmo
 */

#ifndef HAL_RTC_H_
#define HAL_RTC_H_

#include "../../MCAL/07 I2C/I2C_Master.h"

#define Device_Write_address	0xD0			/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1			/* Make LSB bit high of slave address for read operation */
#define hour_12_AM				0x40
#define hour_12_PM				0x60
#define hour_24					0x00
#define TimeFormat12			0x40				/* Define 12 hour format */
#define AMPM					0x20

extern int second,minute,hour,day,date,month,year;
void RTC_Calendar_Write(char _day, char _date, char _month, char _year);
void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM2);
bool IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);


#endif /* HAL_09RTC_RTC_H_ */
