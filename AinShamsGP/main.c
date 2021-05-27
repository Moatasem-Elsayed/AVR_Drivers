#include <stdlib.h>

#include "HAL/Servo.h"
/*
 * main.c
 *
 *  Created on: Apr 8, 2021
 *      Author: PC1
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include "HAL/Motor.h"
#include "Helpers/Std_Types.h"
#include "MCAL/02Timer/Timers.h"
#include "MCAL/03ADC/ADC.h"
#include "UART_Services.h"
#include "MCAL/05UART/UART.h"
#include "HAL/Ultrasonic.h"
#include<string.h>
#include <stdlib.h>
static uint32 tick=0;
volatile uint8 cnt=0;
uint16 values[32]={0};
uint8 recieved_buffer[10]={0};
uint8 stopflag=0;
uint8 i=0;


void RobotMovment();

void HeartRateHandler()
{
	uint16 values[2]={0};
	//1ms
	tick++;
	if(tick==1000)
	{
		uint16 u16AdcRecev=ADC_read();//value between 0 to 1024
		values[cnt]=u16AdcRecev;
		++cnt;
		cnt =cnt% 31;

		tick=0;
	}
}

void RecieveFromBt()
{

	recieved_buffer[i]=UART_ReceiveByteNoBlock();
	i++;
	i=i%10;

}


int main()
{
	uint8_t distance_str[15]={0};
	uint32 OldDistance=0;
	//	ADC_Config_t ADC_config;
	//	//LCD_Init();
	//Timer1_SetInterruptTime_us(1000, HeartRateHandler);//1ms
	//	ADC_config.select_ADC_channel=Single_Ended_Input_On_Channel_1_ADC1;
	//	ADC_config.select_ADC_prescaler=DivisionBy_2;
	//	ADC_config.select_AutoTrigger_source=Free_Running_Mode;
	//	ADC_config.select_reference_voltage=VrefAt_AVCC_pin_AREF_pin;
	//	ADC_init(&ADC_config);
	//sei();
	//Timer0_SetInterruptTime_us(1,MotorHandling);
	//AnalogWrite(OC1B_PD4,80);

	//ultrasonic_init();
	sei();
	MotorInit();
	UART_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RecieveFromBt);

	//Servo_init();

	while(1)
	{

//		ultra_triger();
//		if(distance !=OldDistance)
//		{
//			itoa(distance,(char*)distance_str,10);
//			strcat((char*)distance_str, (char*)" cm ");
//			UART_SendString(distance_str);
//			UART_SendString("\r\n");//0x0D
//			memcpy(distance_str,0,sizeof(distance_str));
//			OldDistance=distance;
//		}
//		if(distance<30 && stopflag==0)
//		{
//			MotorStop(0, 0);
//			UART_SendByte('\r');
//			UART_SendString((uint8*)"Stop Now");
//			UART_SendByte('\r');
//			stopflag=1;
//		}else
		if(i!=0)
		{
			RobotMovment();
			//ServoMovment();
			//stopflag=0;
			i=0;
		}
	}
}


//		if(cnt==30)
//		{
//			uint32 sum=0;
//
//			//LCD_WriteSentence("Entered");
//			for(uint8 i=0; i<30 ;i++)
//			{
//				sum+=values[i];
//			}
//			sum/=30;
//			cli();
//			LCD_WriteNumber((uint32)sum);
//			_delay_ms(2000);
//			sei();
//			cnt=0;
//		}
//

void RobotMovment()
{
	if(recieved_buffer[0]=='F'||recieved_buffer[0]=='f')
	{
		MotorForward(220,220);
		UART_SendByte('\r');
		UART_SendString((uint8*)"Forward Now");
		UART_SendByte('\r');
	}else if(recieved_buffer[0]=='B'||recieved_buffer[0]=='b')
	{
		MotorBackward(220, 2);
		UART_SendByte('\r');
		UART_SendString((uint8*)"Backward Now");
		UART_SendByte('\r');
	}
	else if(recieved_buffer[0]=='R'||recieved_buffer[0]=='r')
	{
		MotorForward(220,200);
		_delay_ms(500);
		MotorRight(170, 230);
		UART_SendByte('\r');
		UART_SendString((uint8*)"Right Now");
		UART_SendByte('\r');
	}else if(recieved_buffer[0]=='L'||recieved_buffer[0]=='l')
	{
		MotorForward(220,200);
		_delay_ms(500);
		MotorLeft(230, 170);
		UART_SendByte('\r');
		UART_SendString((uint8*)"Left Now");
		UART_SendByte('\r');
	}else if(recieved_buffer[0]=='S'||recieved_buffer[0]=='s')
	{
		MotorStop(0, 0);
		UART_SendByte('\r');
		UART_SendString((uint8*)"Stop Now");
		UART_SendByte('\r');
	}else
	{
		UART_SendString((uint8*)"Please enter Valid Character {f-b-r-l-s}");
		UART_SendByte('\r');
	}
}

void ServoMovment()
{
	if(recieved_buffer[0]=='0'||recieved_buffer[0]=='z')
		{
			Servo_Write(0);
			UART_SendByte('\r');
			UART_SendString((uint8*)"Servo 0");
			UART_SendByte('\r');
		}else if(recieved_buffer[0]=='9'||recieved_buffer[0]=='n')
		{
			Servo_Write(90);
			UART_SendByte('\r');
			UART_SendString((uint8*)"Servo 90");
			UART_SendByte('\r');
		}
		else if(recieved_buffer[0]=='8'||recieved_buffer[0]=='e')
		{
			Servo_Write(180);
			UART_SendByte('\r');
			UART_SendString((uint8*)"Servo 180");
			UART_SendByte('\r');
		}
	i=0;
}
