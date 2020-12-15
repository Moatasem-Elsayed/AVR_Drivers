/*
 * Clock.c
 *
 *  Created on: Nov 7, 2020
 *      Author: engmo
 */
#include "Clock.h"

#include <stdio.h>

#include "../HAL/08TFT/TFT.h"
static uint8 global_day=0;
sint8 week[7][20]={
		"Saturday",
		"Sunday",
		"Monday",
		"Tuesday",
		" Wednesday",
		" Thursday",
		" Friday"
};

sint8 months[12][5]={
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sept",
		"Oct",
		"Nov",
		"Dec"
};
void clock_init(uint8  hour ,uint8  minute ,uint8  second ,
		uint8  day ,uint8  month ,uint8 name_day)
{
	sint8 time[]={"00:00:00"};
	sint8 date[20]={0};
global_day=day;
	TFT_Printtext((sint8*)"Digital Clock",25, 50, 2, TFT_RED, TFT_WHITE);
	sprintf((char*)time,(char*)"%.2d:%.2d:%.2d",hour,minute,second);
	TFT_Printtext(time,40, 80, 2, TFT_BLUE, TFT_WHITE);
	sprintf((char*)date,(char*)"%.2d %s %s",day,months[month],(char*)"2020");
	TFT_Printtext(date,40, 120, 2, TFT_PURPLE, TFT_WHITE);

	TFT_Printtext(week[name_day],40, 180, 2, TFT_GREEN, TFT_WHITE);

}

void clock_update()
{
	Timer1_SetInterruptTime_us(1000, Time_Track);

}
void Time_Track(){
	static uint16 tick=0;
	static uint8 hour=23;
	static uint8 minute=59;
	static uint8 second=58;
	static uint8 month=0;
	sint8 time[]="00:00:00";
	sint8 date[20]={0};
	tick++;
	if(tick%1000)
	{
		second++;
		tick=0;
		if(second>=60)
		{
			second=0;
			minute++;
			if(minute>=60)
			{
				minute=0;
				hour++;
				if(hour>=23)
				{
					global_day++;
					hour=0;
					if(global_day>30)
					{
						month++;
					}
					sprintf((char*)date,(char*)"%.2d %s %s",global_day,months[month],(char*)"2020");
					TFT_Printtext(date,40, 120, 2, TFT_PURPLE, TFT_WHITE);
					TFT_Printtext((sint8*)"             ",40, 180, 2, TFT_GREEN, TFT_WHITE);
					TFT_Printtext(week[global_day%7],40, 180, 2, TFT_GREEN, TFT_WHITE);
				}
			}else if (minute>59)
			{

			}

		}
		sprintf((char*)time,(char*)"%.2d:%.2d:%.2d",hour,minute,second);
		TFT_Printtext(time,40, 80, 2, TFT_BLUE, TFT_WHITE);
	}

}
