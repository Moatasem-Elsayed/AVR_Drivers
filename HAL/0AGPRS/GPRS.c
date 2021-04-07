/*
 * GPRS.c
 *
 *  Created on: Mar 31, 2021
 *      Author: PC1
 */
#include "../../Service/UART_Services.h"
#include "GPRS.h"

#include <stdio.h>
#include <util/delay.h>
static uint8 DataOutput[20]={0};
void GPRS_init()
{
	UART_Init();
	UART_SendString((uint8 *)"ATE0\r");//disable echo
    _delay_ms(500);
}
/***************************************/
/* Example Input: "01112932885"        */
/***************************************/
void GPRS_SentMessage(uint8 *Number,uint8*Message)
{
	uint8 FormatCommand[30]={0};

	UART_SendString((uint8 *)"AT+CMGF=1\r");//AT+CMGS At command is used to send SMS message.
	_delay_ms(200);

	sprintf((char*)FormatCommand, (char*)"AT+CMGS=\"+2%s\"\r",Number);
	UART_SendString(FormatCommand);
	_delay_ms(1000);
	//sprintf((char*)FormatCommand, (char*)"%s",Message);
	UART_SendString((uint8 *)Message);
	UART_SendByte(0x1A);

}
/***************************************/
/* Example Input: "01112932885         */
/***************************************/
void GPRS_CallDial(uint8 *Number)
{
	uint8 FormatCommand[30]={0};
	sprintf(FormatCommand,"ATD%s;\r",Number);
	UART_SendString(FormatCommand);

}

uint8* GPRS_GetIPInit()
{

	uint8 FormatCommand[40]={0};
	//UART_SendString("AT+CREG?\r");
	//_delay_ms(2000);
	//UART_SendString("AT+CGATT?\r");//AT+CGATT AT command is used to attach or detach the device to packet domain service. 1 GRPS
//	_delay_ms(2000);
	UART_SendString("AT+CIPSHUT\r");//AT+CIPSHUT will close the GPRS PDP context.
	_delay_ms(2000);
	UART_SendString("AT+CIPMUX=0\r");//AT+CIPMUX AT command configures the device for a single or multi IP connection.
	_delay_ms(2000);
	sprintf(FormatCommand,"AT+CSTT=\"internet.vodafone.net\"\r");
	UART_SendString(FormatCommand);
    _delay_ms(2000);
	//LCD_WriteSentence(DataOutput);
	UART_SendString("AT+CIICR\r");//AT+CIICR command brings up the GPRS or CSD call depending on the configuration previously set by the AT+CSTT command.
    _delay_ms(2000);
	UART_SendString("AT+CIFSR\r");
//	UART_ReceiveString(DataOutput);
	UART_ReceiveString_Asynch(DataOutput);
	sei();
	_delay_ms(8000);
	return DataOutput;

}

uint8* GPRS_GetIp()
{
	UART_SendString("AT+CIFSR\r");
//	UART_ReceiveString(DataOutput);
	UART_ReceiveString_Asynch(DataOutput);
	sei();
	_delay_ms(4000);
	return DataOutput;
}

void  ESPWIFI_URLConnect(uint8 *IP , uint32 Port)
{
	uint8 CommandText[100]={0};
	sprintf((char*)CommandText,(char*)"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",IP,Port);
	UART_SendString((uint8*)CommandText);
	UART_ReceiveString_Asynch(DataOutput);
	sei();
	_delay_ms(4000);
}























