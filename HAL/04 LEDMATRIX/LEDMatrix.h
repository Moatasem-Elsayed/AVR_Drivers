/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v01
*Brief: LED MATRIX COMPONENT
*******************************************************/

#ifndef HAL_LEDMATRIX_LEDMATRIX_H_
#define HAL_LEDMATRIX_LEDMATRIX_H_
#include "Std_Types.h"
#include "Utils.h"


/*********************** Configuration Menu ********************************/
/*********************** Row ******************/
#define LEDMATRIX_ROW0_PORT GPIO_C
#define LEDMATRIX_ROW0_PIN 	PIN_0
#define LEDMATRIX_ROW1_PORT GPIO_C
#define LEDMATRIX_ROW1_PIN 	PIN_1
#define LEDMATRIX_ROW2_PORT GPIO_C
#define LEDMATRIX_ROW2_PIN 	PIN_2
#define LEDMATRIX_ROW3_PORT GPIO_C
#define LEDMATRIX_ROW3_PIN 	PIN_3
#define LEDMATRIX_ROW4_PORT GPIO_C
#define LEDMATRIX_ROW4_PIN 	PIN_4
#define LEDMATRIX_ROW5_PORT GPIO_C
#define LEDMATRIX_ROW5_PIN 	PIN_5
#define LEDMATRIX_ROW6_PORT GPIO_C
#define LEDMATRIX_ROW6_PIN 	PIN_6
#define LEDMATRIX_ROW7_PORT GPIO_C
#define LEDMATRIX_ROW7_PIN 	PIN_7
/*********************** Column ******************/
#define LEDMATRIX_COL0_PORT GPIO_D
#define LEDMATRIX_COL0_PIN 	PIN_0
#define LEDMATRIX_COL1_PORT GPIO_D
#define LEDMATRIX_COL1_PIN 	PIN_1
#define LEDMATRIX_COL2_PORT GPIO_D
#define LEDMATRIX_COL2_PIN 	PIN_2
#define LEDMATRIX_COL3_PORT GPIO_D
#define LEDMATRIX_COL3_PIN 	PIN_3
#define LEDMATRIX_COL4_PORT GPIO_D
#define LEDMATRIX_COL4_PIN 	PIN_4
#define LEDMATRIX_COL5_PORT GPIO_D
#define LEDMATRIX_COL5_PIN 	PIN_5
#define LEDMATRIX_COL6_PORT GPIO_D
#define LEDMATRIX_COL6_PIN 	PIN_6
#define LEDMATRIX_COL7_PORT GPIO_D
#define LEDMATRIX_COL7_PIN 	PIN_7
/*************************** DATA TYPES *****************************************/
typedef enum{
	LED_MATRIX_Column_Cathode=0,
	LED_MATRIX_Column_Anode,
	LED_MATRIX_Column_Wrong
}LEDMATRIX_Type_t;

typedef enum{
	LED_MATRIX_Fail=0,
	LED_MATRIX_Success
}LEDMATRIX_Erorr_t;
/************************** PROTOTYPES ******************************************/
/*Name: 			LEDMATRIX_Init()											*
 * Return:LEDMATRIX_Erorr_t -> LED_MATRIX_Fail,LED_MATRIX_Success			    *
 * GPIO_INPUT: LEDMATRIX_Type_t ->LED_MATRIX_Column_Cathode,LED_MATRIX_Column_Anode  *
 * Brief: 1- make all pins of LEDMATRIX are GPIO_OUTPUT.								*
 * 		  2- Clear All Columns Value											*
 *																				*
 * ******************************************************************************/
LEDMATRIX_Erorr_t LEDMATRIX_Init(LEDMATRIX_Type_t);

/********************************************************************************
 * Name: 			LEDMATRIX_Display()											*
 * Return:LEDMATRIX_Erorr_t -> LED_MATRIX_Fail,LED_MATRIX_Success	     		*
 * GPIO_INPUT: uint8 LEDMATRIX_val[]-> array of the value that you want to display   *
 * 		: uint16 size->No of elements in  arrray								*
 * Brief: Do the Algorithm of the LEDmatrix 								    *
 *																				*
 * ******************************************************************************/
LEDMATRIX_Erorr_t LEDMATRIX_Display(uint8 LEDMATRIX_val[],uint16 size);
#endif /* HAL_04_LEDMATRIX_LEDMATRIX_H_ */
