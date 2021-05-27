#include "ultrasonic.h"

uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t distance;


void ultrasonic_init(void){

  TRIGER_DDR|=(1<<TRIGER);
  ECHO_DDR&=~(1<<ECHO);
  ECHO_PULLUP|=(1<<ECHO);
  enable_ex_interrupt();
TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_8, OCO_DISCONNECTED);
TIMER0_OV_InterruptEnable();
  return;
}

void enable_ex_interrupt(void){

  MCUCR |= (1<<ISC10);		// Trigger INT1 on any logic change.
  GICR  |= (1<<INT1);			// Enable INT1 interrupts.

  return;
}

void ultra_triger(void){
  if(!sensor_working){
    TRIGER_PORT|=(1<<TRIGER);
    _delay_us(10);
    TRIGER_PORT&=~(1<<TRIGER);
    sensor_working=1;
  }
}

ISR(INT1_vect){
  if(sensor_working==1){
    if(rising_edge==0){
      TCNT0=0x00;
      rising_edge=1;
      timer_counter=0;
    }
  else{
    distance=(timer_counter*256+TCNT0)/58.2;

    timer_counter=0;
    rising_edge=0;
    sensor_working=0;
  }
}}

ISR(TIMER0_OVF_vect){
    timer_counter++;
//    if(timer_counter >730){
//      TCNT0=0x00;
//      sensor_working=0;
//      rising_edge=0;
//      timer_counter=0;
//    }
}
