/*
 * Clock.h
 *
 *  Created on: Nov 7, 2020
 *      Author: engmo
 */

#ifndef SERVICE_CLOCK_H_
#define SERVICE_CLOCK_H_

#include "../MCAL/02Timer/Timers.h"
void Time_Track();
void clock_update();
void clock_init(uint8  hour ,uint8  minute ,uint8  second ,
		 	 	uint8  day ,uint8  month ,uint8 name_day);


#endif /* SERVICE_CLOCK_H_ */
