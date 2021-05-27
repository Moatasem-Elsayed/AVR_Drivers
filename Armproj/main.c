#include <stdlib.h>

#include "HAL/Servo.h"
/*
 * main.c
 *
 *  Created on: Apr 8, 2021
 *      Author: PC1
 */
#include <util/delay.h>
#include "Helpers/Std_Types.h"
#include "MCAL/02Timer/Timers.h"
#include "UART_Services.h"
#include "MCAL/05UART/UART.h"


#include "MCAL/01GPIO/GPIO.h"

#define RED_PIN    PIN_6
#define BLUE_PIN   PIN_7

char recieved_buffer[20]={0};
uint8 stopflag=0;
uint8 i=0;
uint16 timeout=0;
//Simple Wait Function
void PostionsSearchColor(uint8_t color);
void Postion1();
void Postion2();
void Postion3();
void OpenHand();
void CloseHand();
void RecieveFromBt()
{
	recieved_buffer[i]=UART_ReceiveByteNoBlock();
	i++;
}


int main()
{

	UART_Init();
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RecieveFromBt);
	LCD_Init();
	Servo_init();
	GPIO_init_pin(GPIO_D, PIN_6, GPIO_INPUT);
	GPIO_set_pullup(GPIO_D, PIN_6);//blue

	GPIO_init_pin(GPIO_D, PIN_7, GPIO_INPUT);
	GPIO_set_pullup(GPIO_D, PIN_7);//red

	sei();
	while(1)
	{
//		LCD_GoTo(1, 0);
//		LCD_WriteNumber2(GPIO_read_pin(GPIO_D, PIN_7));//red
//		//_delay_ms(1000);
//		LCD_GoTo(0, 0);
//		LCD_WriteNumber2(GPIO_read_pin(GPIO_D, PIN_6));//blue
//		//_delay_ms(1000);
#if 1
		//		if(GPIO_read_pin(GPIO_D, PIN_7)==0)
		//		{
		//			LCD_Clear();
		//			LCD_out(1, 0, "RED.");
		//		}
		//		if(GPIO_read_pin(GPIO_D, PIN_6)==0)
		//		{
		//			LCD_Clear();
		//			LCD_out(1, 0, "BLUE");
		//		}

		if(timeout<1000)
		{
			timeout++;
		}
		else if(i!=0)
		{

			LCD_WriteSentence(recieved_buffer);

			if(strstr(recieved_buffer,(char*)"head") != 0 ||strstr(recieved_buffer,(char*)"ache") != 0)
			{
				Postion1();
			}
			if(strstr(recieved_buffer,(char*)"sugar") != 0 ||strstr(recieved_buffer,(char*)"su") != 0)
			{
				Postion2();
			}
			if(strstr(recieved_buffer,(char*)"tack") != 0 ||strstr(recieved_buffer,(char*)"art") != 0)
			{
				Postion3();
			}
			if(strstr(recieved_buffer,(char*)"up") != 0 ||strstr(recieved_buffer,(char*)"Up") != 0)
			{
				ArmDownLunch();
			}
			if(strstr(recieved_buffer,(char*)"down") != 0 ||strstr(recieved_buffer,(char*)"Down") != 0)
			{
				ArmUp();
			}
			if(strstr(recieved_buffer,(char*)"open") != 0 ||strstr(recieved_buffer,(char*)"tch") != 0)
			{
				OpenHand();
			}
			if(strstr(recieved_buffer,(char*)"close") != 0 ||strstr(recieved_buffer,(char*)"leave") != 0)
			{
				CloseHand();
			}
			if(strstr(recieved_buffer,(char*)"red") != 0 ||strstr(recieved_buffer,(char*)"ed") != 0)
			{
				PostionsSearchColor(2);
			}
			if(strstr(recieved_buffer,(char*)"blue") != 0 ||strstr(recieved_buffer,(char*)"lue") != 0)
			{
				PostionsSearchColor(1);
			}
			memset(recieved_buffer,0,sizeof recieved_buffer);

			_delay_ms(1000);
			i=0;
			timeout=0;

		}

#endif
		//*****Base***********
		//				for(int i=25;i>5;i--)//180-0
		//				{
		//					Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		//					_delay_ms(500);
		//				}
		//		for(int i=5;i<25;i++)//0-180
		//		{
		//			Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		//			_delay_ms(500);
		//		}




	}
}
//1 red
//2 blue

void PostionsSearchColor(uint8_t color)
{
	for(int i=5;i<10;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	/**************Up and Down*******/
	ArmDownLunch();
	LCD_GoTo(1, 0);
	LCD_WriteNumber2(GPIO_read_pin(GPIO_D, BLUE_PIN));

	if (color == 1)
	{

		if(GPIO_read_pin(GPIO_D, BLUE_PIN)==0)
		{
			//			LCD_GoTo(1, 0);
			//			LCD_WriteNumber2(GPIO_read_pin(GPIO_D, PIN_7));
			CloseHand();
		}
	}
	else if(color == 2)
	{
		if(GPIO_read_pin(GPIO_D, RED_PIN)==0)
		{
			//			LCD_Clear();
			//			LCD_out(1, 0, "BLUE");
			CloseHand();
		}
	}
	//	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);
	for(int i=10;i<15;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	//	Servo_move(ServoMotor_Right,10);	 //Set servo shaft at -90° position
	//	Servo_move(ServoMotor_Right,200);	 //Set servo shaft at -90° position

	/**************Up and Down*******/
	ArmDownLunch();
	LCD_GoTo(1, 0);
	LCD_WriteNumber2(GPIO_read_pin(GPIO_D, BLUE_PIN));
	if (color == 1)
	{
		if(GPIO_read_pin(GPIO_D, BLUE_PIN) != 1)
		{
			//LCD_Clear();
			//LCD_out(1, 0, "RED.");
			CloseHand();
		}
	}
	else if(color == 2)
	{
		if(GPIO_read_pin(GPIO_D, RED_PIN)==0)
		{
			//LCD_Clear();
			//LCD_out(1, 0, "BLUE");
			CloseHand();
		}
	}
	//	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);
	for(int i=15;i<20;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	//	Servo_move(ServoMotor_Right,10);	 //Set servo shaft at -90° position
	//	Servo_move(ServoMotor_Right,200);	 //Set servo shaft at -90° position

	/**************Up and Down*******/
	ArmDownLunch();
	LCD_GoTo(1, 0);
	LCD_WriteNumber2(GPIO_read_pin(GPIO_D, BLUE_PIN));
	if (color == 1)
	{
		if(GPIO_read_pin(GPIO_D, BLUE_PIN) != 1)
		{
			CloseHand();
		}
	}
	else if(color == 2)
	{
		if(GPIO_read_pin(GPIO_D, RED_PIN)==0)
		{
			CloseHand();
		}
	}
	//	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);


}
void OpenHand()
{
	for(int i=25;i>6;i--)//open
	{
		Servo_move(ServoMotor_Hand,i);	// Set servo shaft at -90° position
		_delay_ms(20);
	}
}
void CloseHand()
{
	for(int i=5;i<=25;i++)//close
	{
		Servo_move(ServoMotor_Hand,i);	// Set servo shaft at -90° position
		_delay_ms(20);
	}
}
void ArmDownLunch()
{
	Servo_move(ServoMotor_Right,10);	 //Set servo shaft at -90° position
	Servo_move(ServoMotor_Right,200);	 //Set servo shaft at -90° position
	for(int j=20;j>=10;j--)//0-180
	{
		Servo_move(ServoMotor_Left,j);	 //Set servo shaft at -90° position
		_delay_ms(120);
	}
}
void ArmUp()
{
	for(int j=10;j<=20;j++)//0-180
	{
		Servo_move(ServoMotor_Left,j);	 //Set servo shaft at -90° position
		_delay_ms(120);
	}
}
void Postion1()
{
	for(int i=5;i<10;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	/**************Up and Down*******/
	ArmDownLunch();
	CloseHand();
	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);
}

void Postion2()
{
	for(int i=10;i<15;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	//	Servo_move(ServoMotor_Right,10);	 //Set servo shaft at -90° position
	//	Servo_move(ServoMotor_Right,200);	 //Set servo shaft at -90° position

	/**************Up and Down*******/
	ArmDownLunch();
	CloseHand();
	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);
}
void Postion3()
{
	for(int i=15;i<20;i++)//0-180
	{
		Servo_move(ServoMotor_Base,i);	 //Set servo shaft at -90° position
		_delay_ms(500);
	}
	/**********Hand************/
	OpenHand();
	//	Servo_move(ServoMotor_Right,10);	 //Set servo shaft at -90° position
	//	Servo_move(ServoMotor_Right,200);	 //Set servo shaft at -90° position

	/**************Up and Down*******/
	ArmDownLunch();
	CloseHand();
	_delay_ms(1000);
	ArmUp();
	_delay_ms(1000);
}
