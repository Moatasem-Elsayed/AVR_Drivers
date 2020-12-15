/*
 * Game.c
 *
 *  Created on: Nov 9, 2020
 *      Author: engmo
 */
#include "Game.h"

#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "../HAL/08TFT/TFT.h"
#include "Clock.h"
#define TURN_SIZE   20
#define  SNAKE_UNIT 10
typedef enum{
	menu_select,
	Digital_Clock,
	Games
}mobile_state_t;

typedef enum{
	up,
	down,
	left,
	right
}direction_state_t;
static uint8 key=0;

void frame(){
#define FRAME_THICK	5

	TFT_DrawRectangle(5, 5, 230,
			FRAME_THICK, TFT_YELLOW);//L1
	TFT_DrawRectangle(5,10, FRAME_THICK,
			300, TFT_YELLOW);//L2
	TFT_DrawRectangle(5, 310, 230,
			FRAME_THICK, TFT_YELLOW);//L3
	TFT_DrawRectangle(230, 10, FRAME_THICK,
			300, TFT_YELLOW);//L4
}
void menu()
{
	static mobile_state_t mobile_state=menu_select;
	uint8 mobile_state_select=Digital_Clock;
	switch(mobile_state){
	case menu_select:
		TFT_Printtext((sint8*)"Digital Clock", 35, 50, 2, TFT_GREEN, TFT_WHITE);
		TFT_Printtext((sint8*)"Games", 35, 65, 2, TFT_GREEN, TFT_WHITE);
		do{
			if(key=='2'){
				TFT_voidPrintChar('>', 15, 50, 2, TFT_GREEN, TFT_WHITE);
				TFT_voidPrintChar(' ', 15, 65, 2, TFT_GREEN, TFT_WHITE);
				mobile_state_select=Digital_Clock;
			}
			else if (key=='5')
			{
				TFT_voidPrintChar(' ', 15, 50, 2, TFT_GREEN, TFT_WHITE);
				TFT_voidPrintChar('>', 15, 65, 2, TFT_GREEN, TFT_WHITE);
				mobile_state_select=Games;
			}else if(key=='#')
			{
				TFT_CLEAR();
				frame();
				mobile_state=mobile_state_select;
				break;
			}
			else
			{
				TFT_voidPrintChar('>', 15, 50, 2, TFT_GREEN, TFT_WHITE);
			}
		}while((key=KEYPAD_get_pressed()));
		break;
	case Digital_Clock:
		clock_init(0,0,0,6,0,6);
		clock_update();
		break;
	case Games:
		snake_game();
		break;
	}

}
void snake_game()
{
	sint16 startx=0,starty=0;
	sint16 endx=0,endy=0;
	uint8 size=10;
	//	uint16 turnx=0;
	//	uint16 turny=0;
	uint8 key=0;
	direction_state_t curr_direction=down,last_direction=down;
	uint16 x[TURN_SIZE]={0};
	uint16 y[TURN_SIZE]={0};
	uint8 record_direction[TURN_SIZE]={down};
	uint8 i=0;
	uint8 j=0;

	TFT_DrawRectangle(110, 20, SNAKE_UNIT,
			SNAKE_UNIT*size, TFT_GREEN);
	startx=110;
	starty=SNAKE_UNIT*size+20;
	endx=110;
	endy=20;

	while(1){
		key=KEYPAD_get_char();
		if(key=='2' && curr_direction != down)//up
		{
			x[i]=startx;
			y[i]=starty;
			record_direction[i]=up;
			i++;
			curr_direction=up;
		}
		else if(key=='8' && curr_direction != up)//down
		{
			x[i]=startx;
			y[i]=starty;
			record_direction[i]=down;
			i++;
			curr_direction=down;
		}
		else if(key=='4' && curr_direction != right)//left
		{
			x[i]=startx;
			y[i]=starty;
			record_direction[i]=left;
			i++;
			curr_direction=left;
		}else if(key=='6' && curr_direction != left)//right
		{
			x[i]=startx;
			y[i]=starty;
			record_direction[i]=right;
			i++;
			curr_direction=right;
		}else if(key=='*')//exit
		{
			break;
		}
		else //last direction
		{
			/*****************************************/
			if(startx>=230)
			{
				startx=10;
			}
			else if(startx<=0)//10
			{
				startx=220;
			}
			/*****************************************/
			if(starty>=310)
			{
				starty=10;
			}
			else if(starty<=0)
			{
				starty=300;
			}
			/*****************************************/
			if(endx>=230)
			{
				endx=10;
			}
			else if(endx<=0)
			{
				endx=220;
			}
			/*****************************************/
			if(endy>=310)
			{
				endy=10;
			}
			else if(endy<=0)
			{
				endy=300;
			}
			/*****************************************/
			switch(curr_direction)//move
			{
			case up:
				TFT_DrawRectangle(startx, starty, SNAKE_UNIT,
						SNAKE_UNIT, TFT_GREEN);
				starty-=SNAKE_UNIT;
				break;
			case down :
				TFT_DrawRectangle(startx, starty, SNAKE_UNIT,
						SNAKE_UNIT, TFT_GREEN);
				starty+=SNAKE_UNIT;
				break;
			case right:
				TFT_DrawRectangle(startx, starty, SNAKE_UNIT,
						SNAKE_UNIT, TFT_GREEN);
				startx+=SNAKE_UNIT;
				break;
			case left :
				TFT_DrawRectangle(startx, starty, SNAKE_UNIT,
						SNAKE_UNIT, TFT_GREEN);
				startx=startx-SNAKE_UNIT;
				break;
			}
			_delay_ms(50);
			switch(last_direction)//clear
			{
			case up:
				TFT_DrawRectangle(endx, endy, SNAKE_UNIT,
						SNAKE_UNIT, TFT_WHITE);
				endy-=SNAKE_UNIT;
				break;
			case down :
				TFT_DrawRectangle(endx, endy, SNAKE_UNIT,
						SNAKE_UNIT, TFT_WHITE);
				endy+=SNAKE_UNIT;
				break;
			case right:
				TFT_DrawRectangle(endx, endy, SNAKE_UNIT,
						SNAKE_UNIT, TFT_WHITE);
				endx+=SNAKE_UNIT;
				break;
			case left :
				TFT_DrawRectangle(endx, endy, SNAKE_UNIT,
						SNAKE_UNIT, TFT_WHITE);
				endx-=SNAKE_UNIT;
				break;
			}
			if(endx==x[j] && endy==y[j])//update last direction
			{
				last_direction=record_direction[j];
				j++;
			}
			else if(i==j) //no change
			{
				x[0]=x[j-1];
				y[0]=y[j-1];
				record_direction[0]=record_direction[j-1];


			}else if ((TURN_SIZE-1)==i && (j!=0))// rotate the index of i to start over
			{
				i=0;
			}else if ((TURN_SIZE-1)==j && (i!=0))// rotate the index of j to start over
			{
				j=0;
			}


		}//else

//		_delay_ms(50);
	}//while


}

