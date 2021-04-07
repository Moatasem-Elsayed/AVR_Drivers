/*
 * main.c
 *
 *  Created on: Apr 3, 2021
 *      Author: PC1
 */
#include "HAL/02 SEG/seg.h"
#include "HAL/03 LCD/LCD.h"


#define F_CPU (8000000UL)


/* OS Header files */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "util/delay.h"


/* program headers*/
#include "STD_TYPES.h"
#include "Utils.h"

/* Tasks Proto. or functions */
void LCD_Task(void* pvParam);
void LED_Task(void* pvParam);
void SEG_Task(void* pvParam);
void Buzzer_Task(void* pvParam);
void SEG2_Task(void* pvParam);


/* OS Object Decl. */
SemaphoreHandle_t			bsUartRes = NULL;
QueueHandle_t qStudentStruct;

int main(void)
{

	/* Init. Pr. */
	//system_init();

	/* OS Object create. */
	//qStudentStruct = xQueueCreate(3, 20); /* msg size Should be 16bytes or more */

	/* Tasks Creation */
	//xTaskCreate(LCD_Task,NULL,500,NULL,4,NULL);
	//configASSERT( xHandle );
	//xTaskCreate(LED_Task,NULL,100,NULL,3,NULL);
	xTaskCreate(SEG2_Task,NULL,200,NULL,2,NULL);
	xTaskCreate(SEG_Task,NULL,200,NULL,2,NULL);

	//xTaskCreate(Buzzer_Task,NULL,100,NULL,1,NULL);

	/* OS Start or sched */
	vTaskStartScheduler();

}

void LED_Task(void* pvParam)
{
	LEDs_init();
	portTickType xLastWakeTime=xTaskGetTickCount();
	const portTickType xFrequency = 300;
	while(1)
	{
		LEDs_toggle();
//        vTaskDelay( 100 );
		vTaskDelayUntil(&xLastWakeTime,xFrequency);

	}
}
void LCD_Task(void* pvParam)
{
	LCD_Init();
	portTickType xLastWakeTime=xTaskGetTickCount();
	const portTickType xFrequency = 400;
//	const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;
char i =0;
	while(1)
	{

		char arr[]="hello Moatasem";
		LCD_WriteChar(arr[i]);
		i=++i%14;
		//LCD_Clear();
//_delay_ms(100000);
		vTaskDelayUntil(&xLastWakeTime,xFrequency);
//        vTaskDelay( 300 );

	}
}

void SEG_Task(void* pvParam)
{
	seg_init(CC_BCD, SEGC_PORT);
	portTickType xLastWakeTime=xTaskGetTickCount();
	const portTickType xFrequency = 20;
	while(1)
	{
		//for(uint8 i=0;i<9;i++)
		{

			seg_write(CC_BCD, SEGC_PORT, 2, SEG1_EN);
//	        vTaskDelay( 200 );
			vTaskDelayUntil(&xLastWakeTime,xFrequency);


		}

	}
}
void SEG2_Task(void* pvParam)
{
	seg_init(CC_BCD, SEGC_PORT);
	portTickType xLastWakeTime=xTaskGetTickCount();
	const portTickType xFrequency = 20;
	while(1)
	{
		//for(uint8 i=0;i<9;i++)
		{
			seg_write(CC_BCD, SEGC_PORT, 1, SEG2_EN);
//	        vTaskDelay( 200 );
			vTaskDelayUntil(&xLastWakeTime,xFrequency);


		}

	}
}

void Buzzer_Task(void* pvParam)
{
	GPIO_init_pin(GPIO_D, PIN_4, GPIO_OUTPUT);//buuzer GPIO_OUTPUT
	while(1)
	{
		for(uint8 i=0;i<9;i++)
		{
			GPIO_write_pin(GPIO_D, PIN_4, HIGH);
			vTaskDelay( 50 );
			GPIO_write_pin(GPIO_D, PIN_4, LOW);
			vTaskDelay( 1000 );


		}

	}
}



