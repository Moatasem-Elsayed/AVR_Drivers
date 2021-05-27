/*
 * GPRS.c
 *
 *  Created on: Mar 31, 2021
 *      Author: PC1
 */
#include "GPRS.h"

#include <stdio.h>
#include <util/delay.h>

#include "../../Service/UART_Services.h"
#include "../03 LCD/LCD.h"
extern  uint8 DataOutput[100];
void GPRS_init()
{
	UART_Init();
	UART_SendString((uint8 *)"ATE0\r");//disable echo
    _delay_ms(500);
//	UART_SendString("AT+CGATT?\r");//AT+CGATT AT command is used to attach or detach the device to packet domain service. 1 GRPS
//	_delay_ms(2000);
//	UART_SendString("AT+CIPMUX=0\r");//AT+CIPMUX AT command configures the device for a single or multi IP connection.
//	_delay_ms(2000);
}
/***************************************/
/* Example Input: "01112932885"        */
/***************************************/
void GPRS_SentMessage(uint8 *Number,uint8*Message)
{
	cli();

	uint8 FormatCommand[30]={0};

	UART_SendString((uint8 *)"AT+CMGF=1\r");//AT+CMGS At command is used to send SMS message.
	_delay_ms(200);
	//AT+CMGS="+201112932885"\r->enter
	sprintf((char*)FormatCommand, (char*)"AT+CMGS=\"+2%s\"\r",Number);
	UART_SendString(FormatCommand);
	_delay_ms(1000);
	UART_SendString((uint8 *)Message);
	UART_SendByte(0x1A);//26 ctrl+z
	sei();

}
/***************************************/
/* Example Input: "01112932885         */
/***************************************/
void GPRS_CallDial(uint8 *Number)
{
	cli();
	uint8 FormatCommand[30]={0};
	//ATD01112932885;enter
	sprintf(FormatCommand,"ATD%s;\r",Number);
	UART_SendString(FormatCommand);
	sei();

}

uint8* GPRS_GetIPInit()//init
{

	uint8 FormatCommand[40]={0};
	//UART_SendString("AT+CREG?\r");
	//_delay_ms(2000);

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
	UART_SendString("AT+CGATT=1\r");//start
	_delay_ms(200);

	UART_SendString("AT+CIFSR\r");//bakah ,ip
	//UART_ReceiveString(DataOutput);//block
	sei();
	UART_ReceiveString_Asynch(DataOutput);
	_delay_ms(8000);
	return DataOutput;

}

uint8* GPRS_GetIp()//getter
{
	cli();
	UART_SendString("AT+CIFSR\r");//bakah ,ip
	//UART_ReceiveString(DataOutput);//while(1);
	UART_ReceiveString_Asynch(DataOutput);//RX interrupt
	sei();
	_delay_ms(4000);
	return DataOutput;
}

void  ThingSpeak_Connect()
{
	cli();
	//184.106.153.149
	//DNS
	UART_SendString((uint8*)"AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r");
	_delay_ms(5000);
	UART_SendString((uint8*)"AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r");
	_delay_ms(5000);
	sei();


}

/*******************
 * Example:SendThingSpeak("field1",100);
 * field1 :from website
 * value :100
 *
 * *********************/
void SendThingSpeak(sint8*field,uint16 val)
{

	memset(DataOutput,0,sizeof(DataOutput));
	uint8 header[200]={0};

	ThingSpeak_Connect();//Connect Server

	cli();
	//	UART_SendString((uint8*)"GET /update?api_key=LE16DO8V2Y6WKF00&field1=200\r\n");
	//GET /update?api_key=LE16DO8V2Y6WKF00&field1=0

	sprintf(header,(char*)"GET /update?api_key=LE16DO8V2Y6WKF00&%s=%d\r\n",field,val);
	UART_SendString((uint8)"AT+CIPSEND\r");
	_delay_ms(2000);
	UART_SendString(header);
	UART_SendByte(0x1A);
	UART_ReceiveString_Asynch(DataOutput);
	sei();
	_delay_ms(5000);
	ThingSpeak_ClosedConnection();




}
void ThingSpeak_ClosedConnection()
{
	UART_SendString("AT+CIPCLOSE=1\r");
	UART_SendByte('\n');
	_delay_ms(4000);
}

/**	sprintf((char*)URL,(char*)"GET /update?api_key=LE16DO8V2Y6WKF00&field1=200\r\n");
//	sprintf((char*)URL,(char*)"GET https://api.thingspeak.com/update?api_key=LE16DO8V2Y6WKF00&field1=0\r");
 *
 * **/
//void ReadThignSpeak(sint8 field,uint8* Dataval)
//{
//	uint8 header[100]={0};
//	uint8 iret=0;
//	sprintf(header,"/channels/1078211/fields/%d.json?results=2",field);
//	ESPWIFI_URLConnect((sint8*)"184.106.153.149", 80);
//	ESPWIFI_GETHTTPMethod(header,DataOutput);
//	strcpy(Dataval,DataOutput);
//}



/* enErorr_t ReadTillReachTo(u8*str,u8 TimeOutFactor)
{
	while(1)
	{
		timeout++;
		u8 iret=MUSART1_u8Receive(&data[i]);
		if(iret!=0&&data[i]!='\r')
		{
			i++;
			timeout=0;
		}
		else if(timeout==(1000*TimeOutFactor))
		{
			volatile char*ptr=strstr((const char*)data,(const char*)str);
			volatile char*endptr=(char*)(ptr+strlen((char*)str));

			if(!memcmp((char*)ptr,(char*)str,endptr-ptr))
			{
				strcpy((char*)recv_data,(char*)data);
				if(!memcmp((char*)ptr,(char*)"+IPD,",5))
				{
					memset(recv_data,0,sizeof(recv_data));
					strcpy((char*)recv_data,(char*)ptr);
				}
				i=0;
				memset(data,0,sizeof(data));
				timeout=0;
				return Success;
			}else
			{
				i=0;
				memset(data,0,sizeof(data));
				timeout=0;
				return Fail;
			}
		}
	}
}

 *
 * */



















