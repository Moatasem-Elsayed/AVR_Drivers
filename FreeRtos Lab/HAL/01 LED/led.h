/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: LED COMPONENT
*******************************************************/

#ifndef LED_H_
#define LED_H_
#include "../../Helpers/Std_Types.h"
#include "../../Helpers/Utils.h"
#include "../../MCAL/01GPIO/GPIO.h"
/********** The hardware configuration of your LEDs***********/
#define LED_PORT		GPIO_D
#define LED_NUM_END		(7)
#define LED_MASK		0xE0//0b1111 0000
typedef enum LEDcolor{
	LEDred=PIN_4,
	LEDyellow=PIN_5,
	LEDgreen=PIN_6,
	LEDblue=PIN_7
	}LED_color_pin_t;
/*****************************************************/
void LED_init(LED_color_pin_t LED_color_pin);
void LEDs_init();	

void LED_on(LED_color_pin_t LED_color_pin);
void LEDs_on();

void LED_off(LED_color_pin_t LED_color_pin);
void LEDs_off();

void LED_toggle(LED_color_pin_t LED_color_pin);
void LEDs_toggle();

void LED_write(LED_color_pin_t LED_color_pin,uint8 val);
void LEDs_write(uint8 val);



#endif /* LED_H_ */
