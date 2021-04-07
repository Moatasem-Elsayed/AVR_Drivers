/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: SEG COMPONENT
*******************************************************/
#include "seg.h"
/*
segment driver can operate four different connection of seven segment 
connection a : 7 parallel  pin for common cathode
connection b : 7 parallel  pin for common anode
connection c : 4 parallel  pin for BCD higher nibble  common cathode
connection d : 4 parallel  pin for BCD higher nibble  common ANODE with note gate through enables   
 */

static char seg_num[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void seg_init(seg_type_t seg_type,uint8 seg_port)
{
	switch(seg_type)
	{
	case CC_Normal:
	case CA_Normal:	GPIO_init_port_mask(seg_port,SEG_MASK_NORMAL);break;

	case CA_BCD:
	case CC_BCD:	GPIO_init_port_mask(seg_port,SEG_MASK_BCD);break;
	}

#if (SEG_EN_STATE==SEG_EN_CONNECTED)
#ifndef _once_
#define _once_
	GPIO_init_pin(SEG_EN1_PORT,SEG1_EN,GPIO_OUTPUT);
	GPIO_init_pin(SEG_EN2_PORT,SEG2_EN,GPIO_OUTPUT);
#endif
#endif

}
void seg_write(seg_type_t seg_type,uint8 seg_port,uint8 val,uint8 seg_en)
{

	switch(seg_type)
	{
	//portc|=0x3f
	case CC_Normal:	GPIO_write_port_clear_mask(seg_port,SEG_MASK_NORMAL);
					GPIO_write_port_set_mask(seg_port,seg_num[val]);break;

	case CA_Normal:	GPIO_write_port_clear_mask(seg_port ,SEG_MASK_NORMAL);
					GPIO_write_port_set_mask(seg_port,~seg_num[val]);break;

	case CC_BCD:	GPIO_write_port_mask(seg_port,val<<4,0xf0);
					break;
	case CA_BCD:
	default:
		break;
	}

#if (SEG_EN_STATE==SEG_EN_CONNECTED)
	if(seg_en==SEG1_EN)
	{
		GPIO_write_pin(SEG_EN1_PORT,SEG1_EN,LOW);//seg1 on
		GPIO_write_pin(SEG_EN2_PORT,SEG2_EN,HIGH);//seg2 off
	}
	else if (seg_en==SEG2_EN)
	{
		GPIO_write_pin(SEG_EN2_PORT,SEG2_EN,LOW);//seg2 on
		GPIO_write_pin(SEG_EN1_PORT,SEG1_EN,HIGH);//seg1 off
	}
	else if(seg_en==SEG_EN_BOTH)
	{
		GPIO_write_pin(SEG_EN2_PORT,SEG2_EN,LOW);//seg2 on
	    GPIO_write_pin(SEG_EN1_PORT,SEG1_EN,LOW);//seg1 on
	}
	else
	{

	}
#endif
} 
