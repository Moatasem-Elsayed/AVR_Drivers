/*****************************************************
 *Author :Moatasem
 *Date:   12/10/2018
 *Version: v01
 *Brief: LED MATRIX COMPONENT
 *******************************************************/

#include <util/delay.h>
#include "LEDMatrix.h"

#include "../../MCAL/01GPIO/GPIO.h"
/***************************Private Function************/
static void LEDMATRIX_SetColumn_value(uint8 val);
static void LEDMATRIX_SetROW(uint8 LEDMATRIX_val[],uint8 LEDMATRIX_index,uint8 pin);
/***************************Global Private Variable ************/

static LEDMATRIX_Type_t gLEDMatrix_TypeSelected=0;

/****************** Functions ***************************/
LEDMATRIX_Erorr_t LEDMATRIX_Init(LEDMATRIX_Type_t LEDMatrix_TypeSelected)
{
	LEDMATRIX_Erorr_t ret=LED_MATRIX_Success;
	gLEDMatrix_TypeSelected=LEDMatrix_TypeSelected;
	if(LEDMatrix_TypeSelected<LED_MATRIX_Column_Wrong)
	{
		/**************** ROWS are GPIO_OUTPUT******************************/
		GPIO_init_pin(LEDMATRIX_ROW0_PORT, LEDMATRIX_ROW0_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW1_PORT, LEDMATRIX_ROW1_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW2_PORT, LEDMATRIX_ROW2_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW3_PORT, LEDMATRIX_ROW3_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW4_PORT, LEDMATRIX_ROW4_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW5_PORT, LEDMATRIX_ROW5_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW6_PORT, LEDMATRIX_ROW6_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_ROW7_PORT, LEDMATRIX_ROW7_PIN, GPIO_OUTPUT);
		/**************** COLUMNs are GPIO_OUTPUT******************************/
		GPIO_init_pin(LEDMATRIX_COL0_PORT, LEDMATRIX_COL0_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL1_PORT, LEDMATRIX_COL1_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL2_PORT, LEDMATRIX_COL2_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL3_PORT, LEDMATRIX_COL3_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL4_PORT, LEDMATRIX_COL4_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL5_PORT, LEDMATRIX_COL5_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL6_PORT, LEDMATRIX_COL6_PIN, GPIO_OUTPUT);
		GPIO_init_pin(LEDMATRIX_COL7_PORT, LEDMATRIX_COL7_PIN, GPIO_OUTPUT);
		switch(LEDMatrix_TypeSelected)
		{
		case LED_MATRIX_Column_Cathode:
			GPIO_write_pin(LEDMATRIX_COL0_PORT, LEDMATRIX_COL0_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL1_PORT, LEDMATRIX_COL1_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL2_PORT, LEDMATRIX_COL2_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL3_PORT, LEDMATRIX_COL3_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL4_PORT, LEDMATRIX_COL4_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL5_PORT, LEDMATRIX_COL5_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL6_PORT, LEDMATRIX_COL6_PIN, GPIO_HIGH);
			GPIO_write_pin(LEDMATRIX_COL7_PORT, LEDMATRIX_COL7_PIN, GPIO_HIGH);
			break;
		case LED_MATRIX_Column_Anode:
			GPIO_write_pin(LEDMATRIX_COL0_PORT, LEDMATRIX_COL0_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL1_PORT, LEDMATRIX_COL1_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL2_PORT, LEDMATRIX_COL2_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL3_PORT, LEDMATRIX_COL3_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL4_PORT, LEDMATRIX_COL4_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL5_PORT, LEDMATRIX_COL5_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL6_PORT, LEDMATRIX_COL6_PIN, GPIO_LOW);
			GPIO_write_pin(LEDMATRIX_COL7_PORT, LEDMATRIX_COL7_PIN, GPIO_LOW);
			break;
		default:
			break;
		}


	}else
	{
		ret=LED_MATRIX_Fail;
	}


	return ret;
}

LEDMATRIX_Erorr_t LEDMATRIX_Display(uint8 LEDMATRIX_val[],uint16 size)
{
	LEDMATRIX_Erorr_t ret=LED_MATRIX_Success;

	if(size>2)
	{
		/******************* Valid GPIO_INPUT **************************/
		for(uint8 cnt=0;cnt<8;cnt++)
		{
			LEDMATRIX_SetColumn_value(cnt);	//set columns sequentially
			for( uint8 i=0;i<8;i++)
			{
				LEDMATRIX_SetROW(LEDMATRIX_val,cnt,i);
			}
		}
	}

	else
	{
		ret=LED_MATRIX_Fail;
	}
	return ret;
}
static void LEDMATRIX_SetROW(uint8 LEDMATRIX_val[],uint8 LEDMATRIX_index,uint8 pin)
{
	uint8 val=0;
	switch(gLEDMatrix_TypeSelected)
	{
	case LED_MATRIX_Column_Cathode:
		break;
	case LED_MATRIX_Column_Anode:
		switch(pin)
		{
		case LEDMATRIX_ROW0_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],0);
			GPIO_write_pin(LEDMATRIX_ROW0_PORT, LEDMATRIX_ROW0_PIN, !val);
			break;
		case LEDMATRIX_ROW1_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],1);
			GPIO_write_pin(LEDMATRIX_ROW1_PORT, LEDMATRIX_ROW1_PIN, !val);
			break;
		case LEDMATRIX_ROW2_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],2);
			GPIO_write_pin(LEDMATRIX_ROW2_PORT, LEDMATRIX_ROW2_PIN, !val);
			break;
		case LEDMATRIX_ROW3_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],3);
			GPIO_write_pin(LEDMATRIX_ROW3_PORT, LEDMATRIX_ROW3_PIN, !val);
			break;
		case LEDMATRIX_ROW4_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],4);
			GPIO_write_pin(LEDMATRIX_ROW4_PORT, LEDMATRIX_ROW4_PIN, !val);
			break;
		case LEDMATRIX_ROW5_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],5);
			GPIO_write_pin(LEDMATRIX_ROW5_PORT, LEDMATRIX_ROW5_PIN, !val);
			break;
		case LEDMATRIX_ROW6_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],6);
			GPIO_write_pin(LEDMATRIX_ROW6_PORT, LEDMATRIX_ROW6_PIN, !val);
			break;
		case LEDMATRIX_ROW7_PIN:
			val=GET_BIT(LEDMATRIX_val[LEDMATRIX_index],7);
			GPIO_write_pin(LEDMATRIX_ROW7_PORT, LEDMATRIX_ROW7_PIN,! val);
			break;
		}
		break;
		default:
			break;
	}

}
static void LEDMATRIX_SetColumn_value(uint8 val)
{

	switch(gLEDMatrix_TypeSelected)
	{
	case LED_MATRIX_Column_Cathode:
		break;
	case LED_MATRIX_Column_Anode:
		/****************RESET Column **************************************/
		GPIO_write_pin(LEDMATRIX_COL0_PORT, LEDMATRIX_COL0_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL1_PORT, LEDMATRIX_COL1_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL2_PORT, LEDMATRIX_COL2_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL3_PORT, LEDMATRIX_COL3_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL4_PORT, LEDMATRIX_COL4_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL5_PORT, LEDMATRIX_COL5_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL6_PORT, LEDMATRIX_COL6_PIN, GPIO_LOW);
		GPIO_write_pin(LEDMATRIX_COL7_PORT, LEDMATRIX_COL7_PIN, GPIO_LOW);
		/****************	SET New Column *********************************/
		switch(val)
		{
		case LEDMATRIX_COL0_PIN:
			GPIO_write_pin(LEDMATRIX_COL0_PORT, LEDMATRIX_COL0_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL1_PIN:
			GPIO_write_pin(LEDMATRIX_COL1_PORT, LEDMATRIX_COL1_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL2_PIN:
			GPIO_write_pin(LEDMATRIX_COL2_PORT, LEDMATRIX_COL2_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL3_PIN:
			GPIO_write_pin(LEDMATRIX_COL3_PORT, LEDMATRIX_COL3_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL4_PIN:
			GPIO_write_pin(LEDMATRIX_COL4_PORT, LEDMATRIX_COL4_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL5_PIN:
			GPIO_write_pin(LEDMATRIX_COL5_PORT, LEDMATRIX_COL5_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL6_PIN:
			GPIO_write_pin(LEDMATRIX_COL6_PORT, LEDMATRIX_COL6_PIN, GPIO_HIGH);
			break;
		case LEDMATRIX_COL7_PIN:
			GPIO_write_pin(LEDMATRIX_COL7_PORT, LEDMATRIX_COL7_PIN, GPIO_HIGH);
			break;
		}
		break;
		case LED_MATRIX_Column_Wrong:
			break;
	}
}
