/*
 * Motor.c
 *
 *  Created on: Apr 8, 2021
 *      Author: PC1
 */
#include "Motor.h"

#include "../MCAL/02Timer/Timers.h"
void MotorInit()
{

GPIO_init_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_OUTPUT);
GPIO_init_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_OUTPUT);
GPIO_init_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_OUTPUT);
GPIO_init_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_OUTPUT);

GPIO_init_pin(MOTORENA_PORT, MOTORENA_PIN, GPIO_OUTPUT);
GPIO_init_pin(MOTORENB_PORT, MOTORENB_PIN, GPIO_OUTPUT);
Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_NON_INVERTING);
ICR1L=255;
ICR1H=0;

}

void MotorForward(uint8 speed1,uint8 speed2)
{
AnalogWrite(OC1B_PD4, speed1);
AnalogWrite(OC1A_PD5, speed2);
GPIO_write_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_HIGH);
GPIO_write_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_LOW);
GPIO_write_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_HIGH);
GPIO_write_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_LOW);

}
void MotorBackward(uint8 speed1,uint8 speed2)
{
	AnalogWrite(OC1B_PD4, speed1);
	AnalogWrite(OC1A_PD5, speed2);
	GPIO_write_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_HIGH);
	GPIO_write_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_HIGH);
}
void MotorLeft(uint8 speed1,uint8 speed2){
	AnalogWrite(OC1B_PD4, speed1);
	AnalogWrite(OC1A_PD5, speed2);
	GPIO_write_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_HIGH);
	GPIO_write_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_HIGH);
	GPIO_write_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_LOW);
}
void MotorRight(uint8 speed1,uint8 speed2)
{
	AnalogWrite(OC1B_PD4, speed1);
	AnalogWrite(OC1A_PD5, speed2);
	GPIO_write_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_HIGH);
	GPIO_write_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_HIGH);
	GPIO_write_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_LOW);
}
void MotorStop(uint8 speed1,uint8 speed2)
{
	AnalogWrite(OC1B_PD4, speed1);
	AnalogWrite(OC1A_PD5, speed2);
	GPIO_write_pin(MOTOR1A_PORT, MOTOR1A_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR2A_PORT, MOTOR2A_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR1B_PORT, MOTOR1B_PIN, GPIO_LOW);
	GPIO_write_pin(MOTOR2B_PORT, MOTOR2B_PIN, GPIO_LOW);
	}

