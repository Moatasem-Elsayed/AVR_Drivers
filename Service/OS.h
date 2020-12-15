/*****************************************************
 *Author :	 Moatasem								*
 *Date:  	 12/10/2018								*
 *Version:	 v02									*
 *Brief:		 DAC Module							*
 ******************************************************/

#ifndef SERIVCE_OS_OS_H_
#define SERIVCE_OS_OS_H_
#include <Std_Types.h>
#include <Utils.h>

#define			NUM_TASKS				3

#define			TASK_SUSPENDED			1
#define			TASK_READY				2

typedef struct
{
	uint16 Period;
	void (*TaskHandler)(void);
	uint16	firstDelay;
	uint8 State;
}Task;

void OS_CreateTask(uint8 Copy_uint8TaskID,uint16 period,void (*ptr)(void),uint16 Copy_uint16firstDelay);
void OS_Start(void);

void OS_SuspendTask(uint8 Copy_uint8TaskID);
void OS_ResumeTask(uint8 Copy_uint8TaskID);
void OS_DeleteTask(uint8 Copy_uint8TaskID);

#endif /* SERIVCE_OS_OS_H_ */
