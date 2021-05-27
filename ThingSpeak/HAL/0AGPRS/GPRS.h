/*
 * GSM.h
 *
 *  Created on: Mar 31, 2021
 *      Author: PC1
 */

#ifndef HAL_0AGPRS_GPRS_H_
#define HAL_0AGPRS_GPRS_H_
#include "../../Helpers/Std_Types.h"

void GPRS_init();
void GPRS_SentMessage(uint8 *Number,uint8*Message);
void GPRS_CallDial(uint8 *Number);
uint8* GPRS_GetIPInit();
uint8* GPRS_GetIp();
void ThingSpeak_Connect();
void ESPWIFI_GETHTTPMethod(sint8*Link , uint8*DataOut);
void SendThingSpeak(sint8*field,uint16 val);
void ReadThignSpeak(sint8 field,uint8* Dataval);

void ThingSpeak_ClosedConnection();


#endif /* HAL_0AGPRS_GPRS_H_ */
