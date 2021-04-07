/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: LED COMPONENT
*******************************************************/
#include "LED.h"


void LED_init(LED_color_pin_t LED_color_pin)
{
volatile uint8 x=0;
x=x+1;
	GPIO_init_pin(LED_PORT,LED_color_pin,GPIO_OUTPUT);
}
void LEDs_init()
{
	GPIO_config_t GPIO_object;
	GPIO_object.port_name=LED_PORT;
	for (uint8 i=0;i<=LED_NUM_END;i++)
	{
		GPIO_object.pin_select[i]=1;
		GPIO_object.pin_direction[i]=GPIO_OUTPUT;
		
	}
	GPIO_set_gpiopad(GPIO_object);
}

void LED_on(LED_color_pin_t LED_color_pin)
{
	GPIO_write_pin(LED_PORT,LED_color_pin,HIGH);
}
void LEDs_on()
{
	GPIO_write_port_set_mask(LED_PORT,LED_MASK);
}
void LED_off(LED_color_pin_t LED_color_pin)
{
	GPIO_write_pin(LED_PORT,LED_color_pin,LOW);
}
void LEDs_off(){
	GPIO_write_port_clear_mask(LED_PORT,LED_MASK);
}

void LED_toggle(LED_color_pin_t LED_color_pin)
{
	static uint8 state=0;
	state=!GPIO_read_pin(LED_PORT, LED_color_pin);
	GPIO_write_pin(LED_PORT,LED_color_pin,state);
}
void LEDs_toggle()
{
	static uint8 state=0;
	state=!state;
	switch(state){
		case 0: GPIO_write_port_clear_mask(LED_PORT,LED_MASK);break;
		case 1:	GPIO_write_port_set_mask(LED_PORT,LED_MASK);break;
	}
}

void LED_write(LED_color_pin_t LED_color_pin,uint8 val){
	GPIO_write_pin(LED_PORT,LED_color_pin,val);
}
void LEDs_write(uint8 val)
{
	GPIO_write_port(LED_PORT,val);
}
