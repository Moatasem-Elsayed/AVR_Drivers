/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: IR Module
*******************************************************/
#ifndef HAL_IR_H_
#define HAL_IR_H_

#include "Std_Types.h"
#include "Utils.h"


/********************Configuration Menu****************/
/* Note  you should use the External interrupt pins */

#define  IR_PORT GPIO_D
#define IR_PIN PIN_2
/****************************************************/
/**
 * @fn void IR_init(IR_Port_Pin_t[], uint8)
 * @brief
 * 			set the IR pins to be GPIO_OUTPUT.
 */
void IR_init();
/**
 * @fn void IR_Enable()
 * @brief
 *
 */
void IR_Enable();
uint8 IR_GetValue();
#endif /* HAL_05_IR_IR_H_ */









