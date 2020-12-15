/*****************************************************
*Author :	 Moatasem								*
*Date:  	 12/10/2018								*
*Version:	 v02									*
*Brief:		 TFT Module								*
******************************************************/
#ifndef HAL_08TFT_TFT_H_
#define HAL_08TFT_TFT_H_
#include "Utils.h"
#include "Std_Types.h"

/***********Configuration Menu*********/
#define RST_PIN   			GPIO_B,1
#define Data_COMMAND_PIN   	GPIO_B,0
#define CS_PIN  		    GPIO_B,4
#define MOSI_PIN   			GPIO_B,5
#define SCK_PIN   			GPIO_B,7

#define     TFT_BLACK        0x0000
#define     TFT_WHITE        0xffff
#define     TFT_RED          0xf800
#define     TFT_BLUE         0x39df
#define     TFT_YELLOW       0xffc0
#define     TFT_ORANGE       0xfd20
#define     TFT_PURPLE       0xf1df
#define     TFT_GREEN        0x1427

#define    TFT_MAX_X       240
#define    TFT_MAX_Y       320

#define   TFT_CHARACTER_WIDTH   6
#define   TFT_CHARACTER_HIGHT   8
/*************************************/
void TFT_init();
void TFT_SetColour(uint16 copy_Colour);
void TFT_DrawRectangle (uint16 copyX ,uint16 copyY , uint16 copyWidth , uint16 copy_Hight , uint16 copyColor );
void TFT_SetAddress (uint16 copy_StartX ,uint16 copy_EndX , uint16 copy_StartY , uint16 copy_EndY);

void TFT_DisplayImage (const uint16* Copy_Image);
void TFT_voidPrintChar(sint8 copy_Char , uint16 copyX ,
					   uint16 copyY, uint8 copy_Size,
				       uint16 copyColor ,uint16 copy_BackColor);
void TFT_Printtext(sint8* copy_Char , uint16 copyX , uint16 copyY
		, uint8 copy_Size , uint16 copyColor , uint16 copy_BackColor);
void TFT_DrawPixel (uint16 copyX , uint16 copyY , uint16 copy_Colour);

void TFT_CLEAR();
#endif /* HAL_08TFT_TFT_H_ */
