/*
 * Motor.h
 *
 *  Created on: Apr 8, 2021
 *      Author: PC1
 */

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_
#include "../HAL/Motor.h"
#include "../MCAL/01GPIO/GPIO.h"
/***********Configurations*************/

#define  MOTOR1A_PIN  PIN_0
#define  MOTOR2A_PIN  PIN_1
#define  MOTOR1B_PIN  PIN_2
#define  MOTOR2B_PIN  PIN_3
#define  MOTORENA_PIN  PIN_4
#define  MOTORENB_PIN  PIN_5


#define  MOTOR1A_PORT	GPIO_A
#define  MOTOR2A_PORT	GPIO_A
#define  MOTOR1B_PORT	GPIO_A
#define  MOTOR2B_PORT	GPIO_A
#define  MOTORENA_PORT  GPIO_D
#define  MOTORENB_PORT  GPIO_D


/*****************************************/


void MotorInit();

void MotorForward(uint8 speed1,uint8 speed2);
void MotorBackward(uint8 speed1,uint8 speed2);
void MotorLeft	(uint8 speed1,uint8 speed2);
void MotorRight(uint8 speed1,uint8 speed2);
void MotorStop(uint8 speed1,uint8 speed2);

#endif /* HAL_MOTOR_H_ */
