/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v03
*Brief: Keypad Module
*LOG:
*		v02 KeypadROW*COL
*		v03 keypadCOL*ROw
*******************************************************/
#include "keypad.h"

#include <util/delay.h>

#include "../../MCAL/01GPIO/GPIO.h"
#define KEYPAD4X4_PROTEUS 1
#ifdef KEYPAD4X4_KIT
static uint8   keypadchars[4][4] = { {'1','2','3','a'},
		{'4','5','6','b'},
		{'7','8','9','c'},
		{'*','0','#','d'}
};
#elif defined(KEYPAD4X4_PROTEUS)
static uint8   keypadchars[4][4] =
{
		{'1','2','3','-'},
		{'4','5','6','*'},
		{'7','8','9','/'},
		{'*','0','#','+'}
};
#endif

void KEYPAD_init()
{
#if		KEYPAD_TYPE	==	KEYPAD3X3
	GPIO_init_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, GPIO_OUTPUT);

	GPIO_set_pullup(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	GPIO_set_pullup(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN);
	GPIO_set_pullup(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN);
#elif		KEYPAD_TYPE	== KEYPAD3X4
	GPIO_init_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, GPIO_INPUT);

	GPIO_init_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, GPIO_OUTPUT);

	GPIO_set_pullup(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	GPIO_set_pullup(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN);
	GPIO_set_pullup(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN);
	GPIO_set_pullup(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN);

#elif 		KEYPAD_TYPE == KEYPAD4X4
	GPIO_init_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, GPIO_INPUT);
	GPIO_init_pin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, GPIO_INPUT);

	GPIO_init_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, GPIO_OUTPUT);
	GPIO_init_pin(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN, GPIO_OUTPUT);

	GPIO_set_pullup(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	GPIO_set_pullup(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN);
	GPIO_set_pullup(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN);
	GPIO_set_pullup(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN);

#endif

}

static void Set_column(){
#if		KEYPAD_TYPE	==	KEYPAD3X3
	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, HIGH);
#elif		KEYPAD_TYPE	== KEYPAD3X4
	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, HIGH);
#elif 		KEYPAD_TYPE == KEYPAD4X4
	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, HIGH);
	GPIO_write_pin(KEYPAD_COL3_PORT, KEYPAD_COL2_PIN, HIGH);

#endif
}
static void Clear_Column(uint8 col_no){
#if		KEYPAD_TYPE	==	KEYPAD3X3
	switch(col_no)
	{
	case 0:	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, LOW);
	break;
	case 1:	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, LOW);
	break;
	case 2:	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, LOW);
	break;
	}
#elif		KEYPAD_TYPE	== KEYPAD3X4
	switch(col_no)
	{
	case 0:	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, LOW);
	break;
	case 1:	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, LOW);
	break;
	case 2:	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, LOW);
	break;
	}
#elif 		KEYPAD_TYPE == KEYPAD4X4
	switch(col_no)
	{
	case 0:	GPIO_write_pin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN, LOW);
	break;
	case 1:	GPIO_write_pin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN, LOW);
	break;
	case 2:	GPIO_write_pin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN, LOW);
	break;
	case 3:	GPIO_write_pin(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN, LOW);
	break;
	}

#endif
}
static uint8 Get_RowValue()
{
	uint8 ret=0;
#if		KEYPAD_TYPE	==	KEYPAD3X3
	ret=GPIO_read_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	ret|=GPIO_read_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN)<<1;
	ret|=GPIO_read_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN)<<2;

#elif		KEYPAD_TYPE	== KEYPAD3X4

	ret=GPIO_read_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	ret|=GPIO_read_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN)<<1;
	ret|=GPIO_read_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN)<<2;
	ret|=GPIO_read_pin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN)<<3;
#elif 		KEYPAD_TYPE == KEYPAD4X4
	ret=GPIO_read_pin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN);
	ret|=GPIO_read_pin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN)<<1;
	ret|=GPIO_read_pin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN)<<2;
	ret|=GPIO_read_pin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN)<<3;

#endif
	return ret;
}

uint8 KEYPAD_get_char()
{
	uint8 col = 0; // counter  For loop
	uint8 row = 0; // get the value of rows in this variable
	uint8 key = 0;

	for(col=0; col<COL_NUM; col++)
	{

		Set_column();		//111
		Clear_Column(col);  //0 (110)
		_delay_ms(10);

		row  = Get_RowValue();//0x0e

		if(row != NOT_PRESSED)
		{
			while(Get_RowValue()!= (NOT_PRESSED));// single pressing
			break;
		}
	}

	if(col == COL_NUM)
	{
		key= 0;
	}
	else
	{
		switch(row){
		case 0b00001110/*14*/ : row = 0; break;
		case 0b00001101/*13*/ : row = 1; break;
		case 0b00001011/*11*/ : row = 2; break;
		case 0b00000111/*7 */ : row = 3; break;
		}
		key  = keypadchars[row][col];
	}
	return key;

}

uint8 KEYPAD_get_pressed(){

	uint8 key=0;
	do
	{
		key = KEYPAD_get_char();
	}while(key == 0);

	return key;
}

