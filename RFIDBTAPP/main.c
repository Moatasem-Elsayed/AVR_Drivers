#include <string.h>

#include "HAL/03 LCD/LCD.h"
#include "MCAL/05UART/UART.h"
#define BUZZER_PORTPIN GPIO_D,PIN_7
/*
 * main.c
 *
 *  Created on: May 18, 2021
 *      Author: PC1
 */
char recieved_buffer[50]={0};
uint8 i=0;
uint8 sayedflag=0;
uint8 Israaflag=0;
//3400661E7539
//3400f06ABC12
//790029BD0CE1
//uint8 admin[15]="790029BD0CE1";
//uint8 Students[2][15]={
//		"661E7539",
//		"F06ABC12",
//};
uint8 AttendaceFlag=0;
uint8 Display[20]={0};
void RecieveFromBt()
{
	//UART_SendString("Hello\n");
	if(sayedflag ==1)
	{
		strcat(Display,"Sayed\n");
	}
	if(Israaflag ==1)
	{
		strcat(Display,"Israa\n");
	}
	sprintf(recieved_buffer,"Attendance=%d\n",AttendaceFlag);
	//UART_SendString(Display);
	strcat(Display,recieved_buffer);
	UART_SendString(Display);
	volatile char x=UDR;
(void)x;
	//_delay_ms(2000);
}
//void BuzzerFlash()
//{
//	GPIO_write_pin(BUZZER_PORTPIN, GPIO_HIGH);
//	_delay_ms(200);
//	GPIO_write_pin(BUZZER_PORTPIN, GPIO_LOW);
//	_delay_ms(200);
//
//	//		_delay_ms(500);
//}
//void BuzzerAlarm()
//{
//	for(int i=0;i<5;i++)
//	{
//		GPIO_write_pin(BUZZER_PORTPIN, GPIO_HIGH);
//		_delay_ms(200);
//		GPIO_write_pin(BUZZER_PORTPIN, GPIO_LOW);
//		_delay_ms(200);
//	}
//}
int main()
{
	GPIO_init_pin(GPIO_C, PIN_0,GPIO_INPUT);
	GPIO_init_pin(GPIO_C, PIN_1,GPIO_INPUT);
	GPIO_set_pullup(GPIO_C, PIN_0);
	GPIO_set_pullup(GPIO_C, PIN_1);
	//LCD_Init();
	UART_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RecieveFromBt);
	sei();
	_delay_ms(3000);
	while(1)
	{
		//		UART_SendString("Hello\n");
		//		_delay_ms(5000);
		if(GPIO_read_pin(GPIO_C, PIN_0)==0 && sayedflag==0)
		{
			sayedflag=1;
			//UART_SendString("Sayed\n");
			AttendaceFlag++;
		}
		if(GPIO_read_pin(GPIO_C, PIN_1)==0 && Israaflag==0 )
		{
			Israaflag=1;
			//UART_SendString("Israa\n");
			AttendaceFlag++;
		}
		AttendaceFlag=(AttendaceFlag >2) ?(AttendaceFlag=2):(AttendaceFlag);
		memset(Display,0, sizeof Display);


	}
}
