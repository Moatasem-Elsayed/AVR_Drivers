/*
 * GSM.h
 *
 *  Created on: Mar 31, 2021
 *      Author: PC1
 */

#ifndef HAL_0AGPRS_GPRS_H_
#define HAL_0AGPRS_GPRS_H_
#include <Std_Types.h>
void GPRS_init();
void GPRS_SentMessage(uint8 *Number,uint8*Message);
void GPRS_CallDial(uint8 *Number);
uint8* GPRS_GetIPInit();
uint8* GPRS_GetIp();


#endif /* HAL_0AGPRS_GPRS_H_ */
