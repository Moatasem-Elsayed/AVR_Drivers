#ifndef _ULTRA_H_
#define _ULTRA_H_

#include<avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../MCAL/02Timer/Timers.h"


#define   TRIGER_DDR    DDRD
#define   ECHO_DDR      DDRD
#define   TRIGER_PORT   PORTD
#define   ECHO_PULLUP   PORTD
#define   TRIGER        6
#define   ECHO          3

/*************************************************
 *  API functions
 *************************************************/

void ultrasonic_init(void);
void enable_ex_interrupt(void);
void ultra_triger(void);
extern uint32_t distance;
#endif
