/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: SEG COMPONENT
*******************************************************/
#ifndef SEG_H_
#define SEG_H_

#include "../../MCAL/01GPIO/GPIO.h"

/****************** masking values*****************************/
#define SEG_MASK_NORMAL		0x7f
/*
 * f0 higher nibble
   0f lower nibble
*/
#define SEG_MASK_BCD		0xf0
#define SEG_EN_CONNECTED	0xFF
#define SEG_EN_BOTH			0xFF
#define SEG_EN_DISCONNECTED	0XDD
#define SEG_EN_NULL         0x08
/************* hardware configuration **************/

#define	SEGA_PORT		GPIO_A
#define	SEGB_PORT		GPIO_B
#define	SEGC_PORT	    GPIO_C
#define SEGD_PORT		GPIO_D

#define SEG_EN1_PORT	GPIO_C
#define SEG_EN2_PORT	GPIO_C
#define SEG_EN_STATE	SEG_EN_CONNECTED
//0---->7
#define SEG1_EN			PIN_2
#define SEG2_EN			PIN_3

/*******************type defenations ***************/
#define SEG_HIGER_NIBBLE(reg,val) (reg&0x0f)|(val<<4)	


/*CC common cathode CA common anode*/

typedef enum stype
{
CC_BCD,//higher nibble
CA_BCD, // higher nibble
CC_Normal, 
CA_Normal,	
}seg_type_t;
/**************************************************/

/***
 * Example:
 *  seg_init( CC_BCD , SEGC_PORT);
 * ***/
void seg_init(seg_type_t seg_type, uint8 SEGA_PORT);
void seg_write(seg_type_t seg,uint8 seg_port,uint8 val,uint8 seg_en);

#endif
