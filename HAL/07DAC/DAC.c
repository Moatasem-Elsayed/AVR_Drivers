/*****************************************************
 *Author :	 Moatasem								*
 *Date:  	 12/10/2018								*
 *Version:	 v02									*
 *Brief:		 DAC Module							*
 ******************************************************/
#include "DAC.h"

#include "../../MCAL/01GPIO/GPIO.h"
#include "../../MCAL/02Timer/Timers.h"
void DAC_Init(uint16 time_us,void (*pf)(void))
{
	GPIO_init_pin(DAC0_PORT, DAC0_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC1_PORT, DAC1_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC2_PORT, DAC2_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC3_PORT, DAC3_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC4_PORT, DAC4_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC5_PORT, DAC5_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC6_PORT, DAC6_PIN, GPIO_OUTPUT);
	GPIO_init_pin(DAC7_PORT, DAC7_PIN, GPIO_OUTPUT);

		Timer1_SetInterruptTime_us(time_us, pf);


}
void DAC_Write(uint8 data[],uint16 size)
{
	static uint16 var = 0;
	var=(var<size)?(var):(0);
	GPIO_write_pin(DAC0_PORT, DAC0_PIN, GET_BIT(data[var],0));
	GPIO_write_pin(DAC1_PORT, DAC1_PIN, GET_BIT(data[var],1));
	GPIO_write_pin(DAC2_PORT, DAC2_PIN, GET_BIT(data[var],2));
	GPIO_write_pin(DAC3_PORT, DAC3_PIN, GET_BIT(data[var],3));
	GPIO_write_pin(DAC4_PORT, DAC4_PIN, GET_BIT(data[var],4));
	GPIO_write_pin(DAC5_PORT, DAC5_PIN, GET_BIT(data[var],5));
	GPIO_write_pin(DAC6_PORT, DAC6_PIN, GET_BIT(data[var],6));
	GPIO_write_pin(DAC7_PORT, DAC7_PIN, GET_BIT(data[var],7));
	var++;


}
void DAC_Disable()
{

		Timer1_Stop();

}
void DAC_restart()
{
		timer1_restart();
}
