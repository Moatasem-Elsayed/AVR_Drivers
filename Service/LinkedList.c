/*****************************************************
 *Author :Moatasem
 *Date:   12/10/2020
 *Version: v02
 *Brief: ....
 *******************************************************/
#include "LinkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "../HAL/03 LCD/LCD.h"
ST_node*Start,*End;
void LinkedList_InitList()
{
	Start=NULL;
	End=NULL;
}
ST_node* LinkedList_CreateNode(uint8 cpy_Name[],uint8 cpy_ID)
{
	ST_node*ptr=NULL;
	/************** Dynamic Array*****************/
	ptr=(ST_node*)malloc(sizeof(ST_node));
	ptr->ID=cpy_ID;
	strcpy((char*)ptr->Name,(char*)cpy_Name);
	return ptr;
}
void LinkedList_insert(ST_node* ptr)
{
	if(Start==NULL&&End==NULL)
	{
		Start=ptr;
		End=ptr;
	}
	else
	{
		End->next=ptr;
		ptr->Prev=End;
		End=ptr;
	}
}
void LinkedList_printList()
{
	ST_node*Temp=Start;
	while(Temp!=NULL)
	{
		LCD_WriteSentence(Temp->Name);
		Temp=Temp->next;
		_delay_ms(1000);
		LCD_Clear();
	}
}

ST_node* LinkedList_Search(int ID)
{
	ST_node*Temp=Start;
	while(Temp!=NULL&&Temp->ID!=ID)
	{
		Temp=Temp->next;
	}
return Temp;
}





