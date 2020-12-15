#ifndef KEYPAD_H
#define KEYPAD_H
#include "Std_Types.h"
#include "Utils.h"



#define ROW_INPUT_COL_OUTPUT	0xf0
#define ROW_PULLUP_COL_HIGH		0xff
#define NOT_PRESSED				0x0f
/**********Configuration Menu***************/
#define KEYPAD_TYPE			KEYPAD3X4
#define COL_NUM					 4

#define KEYPAD_ROW0_PORT 	GPIO_C
#define KEYPAD_ROW0_PIN 	PIN_0
#define KEYPAD_ROW1_PORT 	GPIO_C
#define KEYPAD_ROW1_PIN 	PIN_1
#define KEYPAD_ROW2_PORT 	GPIO_C
#define KEYPAD_ROW2_PIN 	PIN_2
#define KEYPAD_ROW3_PORT 	GPIO_C
#define KEYPAD_ROW3_PIN 	PIN_3

#define KEYPAD_COL0_PORT 	GPIO_C
#define KEYPAD_COL0_PIN 	PIN_4
#define KEYPAD_COL1_PORT 	GPIO_C
#define KEYPAD_COL1_PIN 	PIN_5
#define KEYPAD_COL2_PORT    GPIO_C
#define KEYPAD_COL2_PIN 	PIN_6
#define KEYPAD_COL3_PORT 	GPIO_C
#define KEYPAD_COL3_PIN 	PIN_7

/*****************************************/
/*****************************************/
#define KEYPAD4X4		0
#define KEYPAD3X3		1
#define KEYPAD3X4		2

/******************************************/

void KEYPAD_init();
uint8 KEYPAD_get_char();
uint8 KEYPAD_get_pressed();



#endif // KEYPAD_H
