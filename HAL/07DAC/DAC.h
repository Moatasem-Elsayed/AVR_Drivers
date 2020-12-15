/*****************************************************
*Author :	 Moatasem								*
*Date:  	 12/10/2018								*
*Version:	 v02									*
*Brief:		 DAC Module								*
******************************************************/
#ifndef HAL_DAC_H_
#define HAL_DAC_H_
#include "Std_Types.h"
#include "Utils.h"

/***********Configuration Menu**********************/
#define DAC0_PORT 	GPIO_C
#define DAC0_PIN 	PIN_0
#define DAC1_PORT 	GPIO_C
#define DAC1_PIN 	PIN_1
#define DAC2_PORT 	GPIO_C
#define DAC2_PIN 	PIN_2
#define DAC3_PORT	 GPIO_C
#define DAC3_PIN 	PIN_3
#define DAC4_PORT 	GPIO_C
#define DAC4_PIN 	PIN_4
#define DAC5_PORT 	GPIO_C
#define DAC5_PIN 	PIN_5
#define DAC6_PORT 	GPIO_C
#define DAC6_PIN 	PIN_6
#define DAC7_PORT 	GPIO_C
#define DAC7_PIN 	PIN_7
/***************************************************/
/**
 * @fn void DAC_Init()
 * @brief
 * 		set pins GPIO_OUTPUT
 *		adjust sampling rate and set callback function
 */
void DAC_Init(uint16 time_us,void (*pf)(void));
/**
 * @fn void DAC_Write(uint8[], uint16)
 * @brief
 *			write on the port the values of DAC sequentially
 * @param data sampling values of DAC
 * @param size size of sampling values
 */
void DAC_Write(uint8 data[],uint16 size);
/**
 * @fn void DAC_Disable()
 * @brief
 * Stop timer
 */
void DAC_Disable();
/**
 * @fn void DAC_restart()
 * @brief
 * restart Timer
 */
void DAC_restart();
#endif /* HAL_DAC_H_ */
