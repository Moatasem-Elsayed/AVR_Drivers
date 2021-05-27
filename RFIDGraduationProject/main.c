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
//3400661E7539
//3400f06ABC12
//790029BD0CE1
uint8 admin[15]="790029BD0CE1";
uint8 Students[2][15]={
		"661E7539",
		"F06ABC12",
};
uint8 AttendaceFlag=0;
void RecieveFromBt()
{
	recieved_buffer[i]=UART_ReceiveByteNoBlock();
	i++;
}
void BuzzerFlash()
{
	GPIO_write_pin(BUZZER_PORTPIN, GPIO_HIGH);
	_delay_ms(200);
	GPIO_write_pin(BUZZER_PORTPIN, GPIO_LOW);
	_delay_ms(200);

	//		_delay_ms(500);
}
void BuzzerAlarm()
{
	for(int i=0;i<5;i++)
	{
		GPIO_write_pin(BUZZER_PORTPIN, GPIO_HIGH);
		_delay_ms(200);
		GPIO_write_pin(BUZZER_PORTPIN, GPIO_LOW);
		_delay_ms(200);
	}
}
int main()
{
	GPIO_init_pin(BUZZER_PORTPIN, GPIO_OUTPUT);
	GPIO_init_pin(GPIO_C, PIN_0,GPIO_OUTPUT);
	GPIO_init_pin(GPIO_C, PIN_1,GPIO_OUTPUT);

	GPIO_write_pin(GPIO_C, PIN_0,GPIO_HIGH);
	GPIO_write_pin(GPIO_C, PIN_1,GPIO_HIGH);

	LCD_Init();
	UART_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RecieveFromBt);
	sei();

	while(1)
	{
		//UART_SendString("Israa\nSayed\nAttendance=2\n");
//		_delay_ms(5000);
		if(i!=0)
		{
			//LCD_out(1, 0, recieved_buffer);
			LCD_Clear();
			LCD_out(1, 0, "Card is Here");
			if(strstr(recieved_buffer,Students[0])!=0)
			{
				LCD_out(0, 0, "Welcome Sayed");
				GPIO_write_pin(GPIO_C, PIN_0,GPIO_LOW);
				BuzzerFlash();
				AttendaceFlag++;
			}
			else if(strstr(recieved_buffer,Students[1])!=0)
			{
				LCD_out(0, 0, "Welcome Israa");
				GPIO_write_pin(GPIO_C, PIN_1,GPIO_LOW);

				BuzzerFlash();
				AttendaceFlag++;

			}else if(strstr(recieved_buffer,admin)!=0)
			{

				LCD_out(0, 0, "Attendance ");
				AttendaceFlag=(AttendaceFlag >2) ?(AttendaceFlag=2):(AttendaceFlag);
				LCD_WriteNumber(AttendaceFlag);
				BuzzerFlash();
			}
			else
			{
				LCD_out(0, 0, "Wrong Card....");
				BuzzerAlarm();
				LCD_Clear();
			}
			i=0;
		}


	}
}
