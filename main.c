/**************** HELPER***************************************/

#include "MCAL/03ADC/ADC.h"
#include "MCAL/01GPIO/GPIO.h"
#include <Mem_Map32.h>
#include <string.h>
#include <Std_Types.h>
#include <util/delay.h>
#include "Service/UART_Services.h"

#include "HAL/03 LCD/LCD.h"
#include "MCAL/05UART/UART.h"

/************************************************************/
#define IR         0
#define LEDMATRIX  0
#define ADC        0
#define TIMER      0
#define LCD        1
#define SEG        0
#define BUTTON     0
#define BUZZER     0
#define LED        0
#define INTERUUPT  0
#define TFT        0
#define SPI        0
#define I2C			0
#define OS_SCH     0
#define KEYPAD     0
#define USART      1
#define DAC        0
#define EEPROM     0
#define APP1	   0
#define LINKEDLIST 0
/************************************************************/
/******************* Global Variables **********************/
GPIO_interrupt_t button_interrupt;
ADC_Config_t ADC_config;
uint8 recieved_buffer[50]={0};
uint16 timeout=0;
uint8 i=0;
/************************************************************/
/********* Timer1 callback Btn_Callbackction ***************/
#if LED
void led_blink(){
	static uint16 cnt=0;
	cnt++;
	if(cnt==1000)//1 second
	{
		LED_toggle(LEDblue);
		cnt=0;
	}
}
#endif
/********* Button Ext0 callback Btn_Callbackction ***************/
#if BUTTON
void Btn_Callback(){

	static uint8 num='0';				// ASCII value for '0'
	num++;							//Increment X to be '1' till '9'
	LCD_out(1, 1, (uint8*)"Ahmed");
	LCD_WriteChar(num);	//display the numbers on LCD
	num=(num=='9')?('0'):(num);			//check if the x is more than '9' back again to be '0'

}
#endif
/********* TIMER0 callback Btn_Callbackction ***************/
#if TIMER
void Timer_interrupt(){
	//1us
	static uint32 cnt=0;
	cnt++;
	/******************************/
	/*
	 * Ferquency=8MHZ
	 * Prescalar=8
	 * PULSE Duration:1us
	 * OCR=200
	 * OCR interrupt FLag will raise at 200 us
	 * 200us*5000=1 second
	 ******************************/
	if(cnt==5000)
	{
		LED_toggle(LEDgreen);//Toggle led every 1 second
		cnt=0;
	}
}
#endif
/************DAC callback Btn_Callbackction***************/
#if DAC
void Sin_format()
{
	DAC_Write(sin_format,1023);
}
#endif
/****************Scheduler tasks********************/
#if OS_SCH
void task1(){
	LED_toggle(LEDblue);
}
void task2(){
	LED_toggle(LEDgreen);
}
void task3(){

	LED_toggle(LEDyellow);

}
#endif
/*************************************************************/
#if USART
void RecieveFromBt()
{

	recieved_buffer[i]=UART_ReceiveByteNoBlock();
	i++;
//	timeout=0;
}
#endif
int main(){
	/***************** LOCAL Variables **********************/
	//	uint16 u16AdcRecev=0,u16old_val=0;
#if INTERUUPT
	//	/***************** INTERRUPT init **********************/
	button_interrupt.interruptBtn_CallbackctionPtr=Btn_Callback;//set Btn_Callbackction to callback Btn_Callbackction
	button_interrupt.interruptPinSelect=EXT_INTERRPUT_INT0_PD2 ;//select external interrupt pin
	button_interrupt.interruptSenseControl=FALLING_EDGE_OF_INTERRUPT;//select type of edge detector
	GPIO_init_interrupt(&button_interrupt);//call init Btn_Callbackction to prepared interrupt to use
#endif
	/***************** LED init **********************/
#if LED
	LED_init(LEDblue); //make led on pin7 GPIO_OUTPUT
	LED_init(LEDgreen); //make led on pin6 GPIO_OUTPUT
#endif
	/***************** BUZZER init **********************/
#if BUZZER
	GPIO_init_pin(GPIO_D, PIN_4, GPIO_OUTPUT);//buuzer GPIO_OUTPUT
#endif
	/***************** BUTTON init **********************/
#if BUTTON
	GPIO_init_pin(GPIO_D, PIN_2, GPIO_INPUT); //button GPIO_INPUT
	GPIO_set_pullup(GPIO_D, PIN_2); //pullup
#endif
	/***************** SEVEN SEGMENT init **********************/
#if SEG
	seg_init(CC_BCD, SEGC_PORT);
	seg_write(CC_BCD, SEGC_PORT, 2, SEG1_EN);
#endif
	/***************** LCD init **********************/
#if LCD
	LCD_Init();
#endif
	/***************** TIMER0 init **********************/
#if TIMER
	TIMER0_Init(TIMER0_CTC_MODE, TIMER0_SCALER_8, OCO_DISCONNECTED);
	TIMER0_Compare_reload(200); // after every 201 pulse the timer will generate interrupt
	TIMER0_CMP_SetCallBack(Timer_interrupt);
	TIMER0_OC_InterruptEnable();
	/***************** TIMER1 init **********************/
	Timer1_SetInterruptTime_us(1000, led_blink);
#endif

	/**************** ADC_INIT *************************/
#if ADC
	ADC_config.select_ADC_channel=Single_Ended_Input_On_Channel_1_ADC1;
	ADC_config.select_ADC_prescaler=DivisionBy_8;
	ADC_config.select_AutoTrigger_source=Free_Running_Mode;
	ADC_config.select_reference_voltage=VrefAt_Internal_2560mV;
	ADC_init(&ADC_config);
#endif
	/***************** LED MATRIX INIT **********************/
#if LEDMATRIX
	LEDMATRIX_Init(LED_MATRIX_Column_Anode);
#endif
	/*********************IR Receiving***************************/
#if IR
	IR_init();// pin is GPIO_INPUT
	IR_Enable(); //start IR to recieve
#endif
	/********************EEPROM****************************/
#if EEPROM
	if(EEPROM_read(0x03)=='A')
	{
		LCD_WriteChar(EEPROM_read(0x03));
		LCD_WriteNumber(EEPROM_read(0x03));

		uint32 val=EEPROM_READ_4byte(0x04);
		LCD_GoTo(1, 0);
		LCD_WriteNumber(val);


	}
	else
	{	EEPROM_write(0x03, 'A');
	EEPROM_WRITE_4byte(0x04,1200);

	}
#endif
	/************************DAC*************************/
#if DAC
	DAC_Init(1,Sin_format);
#endif
	/********************* USART ****************************/
#if USART
	UART_Init();

	//	UART_SendByte('A');
		UART_SendString("hello");
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RecieveFromBt);
#endif
	/**************** KEYPAD********************************/
#if KEYPAD
	KEYPAD_init();
#endif
	/*****************Scheduler***************************/
#if OS_SCH
	LED_init(LEDyellow);
	LED_init(LEDblue);
	LED_init(LEDgreen);
	OS_CreateTask(0, 1000, task1, 0);//7
	OS_CreateTask(1, 1000, task2, 1000);//6
	OS_CreateTask(2, 1000, task3, 2000);//5
	OS_Start();
#endif
	/************** Linked List***********************/
#if LINKEDLIST
	ST_node*Temp=NULL;
	LinkedList_InitList();

	Temp=LinkedList_CreateNode((uint8*)"Moatasem", 11);
	LinkedList_insert(Temp);
	Temp=LinkedList_CreateNode((uint8*)"Ali", 22);
	LinkedList_insert(Temp);
	Temp=LinkedList_CreateNode((uint8*)"Mohamed", 33);
	LinkedList_insert(Temp);

	Temp=LinkedList_Search(44);

	if( Temp==NULL)
	{
		LCD_WriteSentence("NOT Exist");
		//not exist
	}
	else
	{
		LCD_WriteSentence(Temp->Name);
	}
	LinkedList_printList();
#endif
	/************SPI**********************************/
#if SPI
	GPIO_init_pin(GPIO_B, 5, GPIO_OUTPUT);//Mosi
	GPIO_init_pin(GPIO_B, 7, GPIO_OUTPUT);//sck
	GPIO_init_pin(GPIO_B, 4, GPIO_OUTPUT);//ss
	GPIO_init_pin(GPIO_B, 6, GPIO_INPUT);//Miso

	GPIO_write_pin(GPIO_B, 4, HIGH);//disable slave 						/* Disable slave initially by making high on SS pin */
	SPI_Init();
#endif
	/*************TFT****************************/
#if TFT
	TFT_init();
	TFT_DrawRectangle(135, 20, 10,
			125, TFT_BLUE);
	_delay_ms(2000);
	TFT_DrawRectangle(50, 50, 160, 160, TFT_GREEN);
	_delay_ms(2000);
	TFT_DrawRectangle(40, 80, 100,
			20, TFT_BLUE);
	frame();
	clock_init(0,0,0,6,0,6);
	clock_update();
	//		TFT_DisplayImage(image);
#endif
	/***************** RTC ***************************/
#if RTC
	I2C_Init();
	RTC_Clock_Write(0x11, 0x59, 0x00, hour_12_PM);/* Write Hour Minute Second Format */
	RTC_Calendar_Write(0x07, 0x31, 0x12, 0x16);	/* Write day date month and year */
	while(1);
#endif

	/*************************************************/
#if I2C
	char buffer[20];
	char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	I2C_Init();										/* Initialize I2C */
	I2C_Start_Wait(0x00);
#endif
	/***************** END INIT **********************/
	sei(); ///enable global interrupt
	while(1)
	{
#if I2C
		uint8 size=strlen("moatasem");
		for(int i=0;i<size;i++)
		{
			//			GPIO_write_pin(GPIO_B, 4, LOW);//enable slave
			I2C_Write("moatasem"[i]);
			_delay_ms(500);
		}
#endif
#if 0
		RTC_Read_Clock(0);							/* Read the clock with second address i.e location is 0 */
		if (hour & TimeFormat12)
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			if(IsItPM(hour))
				strcat(buffer, "PM");
			else
				strcat(buffer, "AM");
			LCD_out(0, 0, buffer);
		}
		else
		{
			sprintf(buffer, "%02x:%02x:%02x  ", (hour & 0b00011111), minute, second);
			LCD_out(0, 0, buffer);
		}
		RTC_Read_Calendar(3);						/* Read the calender with day address i.e location is 3 */
		sprintf(buffer, "%02x/%02x/20%02x %3s ", date, month, year,days[day-1]);
		LCD_out(1, 0, buffer);
#endif
#if USART
		if(i!=0)
		{

				LCD_Clear();
				LCD_WriteSentence(recieved_buffer);
				_delay_ms(1000);
				i=0;
				memset(recieved_buffer,0,sizeof(recieved_buffer));

		}
#endif
#if TFT
		snake_game();
		menu();
		Game_Select();
#endif

#if SPI
		uint8 size=strlen("moatasem");
		for(int i=0;i<size;i++)
		{
			GPIO_write_pin(GPIO_B, 4, LOW);//enable slave
			SPI_Write("moatasem"[i]);
			_delay_ms(500);
		}
#endif

#if KEYPAD
		uint8 key=KEYPAD_get_pressed();
		LCD_WriteChar(key);
#endif

#if IR
		if(IR_GetValue()==70)
		{
			LED_on(LEDblue);
			LCD_WriteNumber(IR_GetValue());
		}
		else if(IR_GetValue()==69)
		{
			LED_off(LEDblue);
			LCD_WriteNumber(IR_GetValue());
		}
#endif
		/*********************************************
		 * 	 seven segment     *
		 ********************************************/
#if APP1
		for(int i=0;i<=9;i++)
		{
			for(int j=0;j<=9;j++)
			{
				for(int z=0;z<=50;z++)
				{
					seg_write(CC_BCD, SEGC_PORT, i, SEG1_EN);
					_delay_ms(5);
					seg_write(CC_BCD, SEGC_PORT, j, SEG2_EN);
					_delay_ms(5);
				}
				/*********************************************
				 * 	 Set the Alarm depend on Potentiometer  *
				 ********************************************/

				u16AdcRecev=ADC_read();//value between 0 to 1024
				if(u16AdcRecev!=u16old_val)
				{
					cli(); //critical section protection
					LCD_Clear();
					LCD_GoTo(0, 0);
					LCD_WriteNumber((uint16)u16AdcRecev);
					u16old_val=u16AdcRecev;
					sei();//critical section protection

					if(u16AdcRecev>=500)
					{
						GPIO_write_pin(GPIO_D, PIN_4, HIGH);
					}
					else
					{
						GPIO_write_pin(GPIO_D, PIN_4, LOW);
					}
				}
				else
				{

				}


			}
		}

#endif

#if LEDMATRIX
		uint8 M[]={/*M*/0,0, 126, 2, 14, 14, 2, 126, 0,/*0*/0, 126, 66, 66, 66, 66,
				126, 0,/*T*/0, 2, 2, 126, 2, 2, 0, 0,/*A*/0, 0, 126, 18, 18, 126, 0, 0,
				/*s*/0, 0, 116, 84, 84, 92, 0,0/*E*/,0, 0, 126, 82, 82, 82, 0, 0,
				/*M*/0,0, 126, 2, 14, 14, 2, 126, 0,0
		};

		char data[]={0, 252, 36, 36, 36, 252, 0, 0};
		for(uint8 i=0;i<sizeof(M)-9;i++)
		{
			for(uint8 j=0;j<200;j++)
				LEDMATRIX_Display(&M[i],8);

		}
#endif
	}//while(1)
}//main
