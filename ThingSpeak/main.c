/*
 * main.c
 *
 *  Created on: Apr 8, 2021
 *      Author: PC1
 */
#include "HAL/03 LCD/LCD.h"
#include "HAL/0AGPRS/GPRS.h"
 uint8 DataOutput[100]={0};

int main()
{
	GPRS_init();
	LCD_Init();

	LCD_WriteSentence(GPRS_GetIPInit());//takes 16 second

	extern int jcount;
	jcount=0;
	//LCD_WriteNumber(jcount);
	//GPRS_SentMessage("01112932885","Moatasem is Genius");
	//GPRS_CallDial("01112932885");
	while(1)
	{
		jcount=0;
		//LCD_WriteSentence(GPRS_GetIp());

			SendThingSpeak("field1",300);
//
			LCD_Clear();
			LCD_GoTo(1, 1);
			LCD_WriteSentence("#");
			LCD_WriteSentence(DataOutput);
			LCD_GoTo(0, 1);
			LCD_WriteSentence(DataOutput);

	}
}
