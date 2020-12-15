/*****************************************************
 *Author :	 Moatasem								*
 *Date:  	 12/10/2018								*
 *Version:	 v02									*
 *Brief:		 DAC Module							*
 ******************************************************/
#include "OS.h"
#include <stddef.h>

#include "../MCAL/02Timer/Timers.h"
static void OS_SCHEDULER(void);
static Task OStasks[NUM_TASKS] ;


void OS_CreateTask(uint8 uint8TaskID,uint16 period,void (*ptr)(void),uint16 uint16firstDelay)
{
	OStasks[uint8TaskID].Period = period;
	OStasks[uint8TaskID].TaskHandler = ptr;
	OStasks[uint8TaskID].firstDelay = uint16firstDelay;
	OStasks[uint8TaskID].State = TASK_READY;
}

void OS_Start(void)
{

	Timer1_SetInterruptTime_us(1000 , OS_SCHEDULER );

}

void OS_SuspendTask(uint8 uint8TaskID)
{
	OStasks[uint8TaskID].State=TASK_SUSPENDED;
}

void OS_ResumeTask(uint8 uint8TaskID)
{
	OStasks[uint8TaskID].State=TASK_READY;
}

void OS_DeleteTask(uint8 uint8TaskID)
{
	OStasks[uint8TaskID].TaskHandler=NULL;
}


static void OS_SCHEDULER(void)
{
//	static uint16 tick=0;
//	tick++;
//	if (tick==1000)
	{
		uint8 counter;
		/*Loop on the tasks*/
		for(counter=0;counter<NUM_TASKS;counter++)
		{
			/*Check that task isn't deleted or suspended */
			if( (OStasks[counter].State == TASK_READY) )
			{
				/*Check until the first delay equal to zero*/
				if(OStasks[counter].firstDelay == 0)
				{
					OStasks[counter].firstDelay=OStasks[counter].Period-1;
					/*Invoke the task function*/
					OStasks[counter].TaskHandler();
				}
				else
				{
					/*Decrement the first delay*/
					OStasks[counter].firstDelay--;
				}
			}
			else
			{
				/*Do nothing*/
			}
		}
//tick=0;
	}
}
