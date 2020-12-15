/*****************************************************
 *Author :Moatasem
 *Date:   12/10/2018
 *Version: v02
 *Brief: IR Module
 *******************************************************/
#include "IR.h"

#include <string.h>

#include "../../MCAL/01GPIO/GPIO.h"
#include "../../MCAL/02Timer/Timers.h"
#include "../01 LED/led.h"
#include "../03 LCD/LCD.h"
static volatile uint8 start_bit=0;
static volatile uint8 Frame_cnt=0;
static volatile uint32 Frame[100]={0};
static volatile uint8 value=0;
void Format_Response();
void Bit_Request();
/**
 * @fn void IR_init()
 * @brief
 *
 */
void IR_init()
{
	GPIO_init_pin(IR_PORT, IR_PIN, GPIO_INPUT);
}

void IR_Enable()
{

	GPIO_interrupt_t IR_signal;

	IR_signal.interruptFunctionPtr=Bit_Request;//set function to callback function
	switch(IR_PORT)
	{
	case GPIO_D:

		switch(IR_PIN)
		{
		case PIN_2: IR_signal.interruptPinSelect=EXT_INTERRPUT_INT0_PD2 ;//select external interrupt pin
		break;
		case PIN_3: IR_signal.interruptPinSelect=EXT_INTERRPUT_INT1_PD3 ;//select external interrupt pin
		break;
		}
		break;

		case GPIO_B:
			IR_signal.interruptPinSelect=EXT_INTERRPUT_INT2_PB2 ;//select external interrupt pin
			break;
		default:break;
	}
	IR_signal.interruptSenseControl=FALLING_EDGE_OF_INTERRUPT;//select type of edge detector
	GPIO_init_interrupt(&IR_signal);//call init function to prepared interrupt to use
}
//32 bit
void Bit_Request()
{
	if(start_bit==0)
	{
		Timer1_SetInterruptTime_us(60,Format_Response);

		start_bit=1;
	}
	else
	{
		Frame[Frame_cnt]=Get_Current_Timer1();//13.5ms //2.25ms //1.25ms
		Timer1_SetInterruptTime_us(60,Format_Response);
		Frame_cnt++;

	}

}

void Format_Response(){

	static uint8 tick=0;
	tick++;
	if(tick==16)//1 second
	{
		for(uint8 i=0;i<8;i++)

		{
			if(Frame[17+i]>=2000&&Frame[17+i]<=2500)
			{
				SET_BIT(value,i);
			}
			else
			{
				CLEAR_BIT(value,i);
			}
		}
		tick=0;
		start_bit=0;
		memset((uint8*)Frame,0,sizeof(Frame));
		Frame_cnt=0;
	}
}


uint8 IR_GetValue(){
	return value;
}





