/*
 * Servo.h
 *
 *  Created on: Apr 13, 2021
 *      Author: PC1
 */

#ifndef HAL_SERVO_H_
#define HAL_SERVO_H_
#include "../MCAL/01GPIO/GPIO.h"
#include "../MCAL/02Timer/Timers.h"
#include <util/delay.h>

#define SERVO_PORT GPIO_D
#define SERVO_PIN  PIN_7

void Servo_init();
void Servo_Write(uint8 angle);

#endif /* HAL_SERVO_H_ */
