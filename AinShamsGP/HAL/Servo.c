/*
 * Servo.c
 *
 *  Created on: Apr 13, 2021
 *      Author: PC1
 */

#include "Servo.h"

#include "../Helpers/Utils.h"
static uint16 tick =0;
static uint16 duty =0;

void ServoHandler()
{
	tick++;
	if(tick==200)//1ms
	{
		SET_BIT(PORTD,SERVO_PIN);
		tick=0;
	}else if (tick == duty)
	{
		CLEAR_BIT(PORTD,SERVO_PIN);

	}

}
void Servo_init()
{
	GPIO_init_pin(SERVO_PORT, SERVO_PIN, GPIO_OUTPUT);
	Timer2_SetInterruptTime_us(100,ServoHandler);
}
void Servo_Write(uint8 angle)
{
	switch(angle)
	{
	case 0:duty=15;break;
	case 90:duty=20;break;
	case 180:duty=10;break;
	}

}
