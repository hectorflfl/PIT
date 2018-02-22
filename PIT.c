/*
 *
 * PIT.c
 *
 *  Created on: Feb 21, 2018
 *      Author: carlo
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"

#define PIT_CLOCK_GATING 0x800000
#define DISABLED 		 0x0
#define FIRSTBIT		0x1
#define PIT_MCR 		 0x2
#define ENABLE			 ~(0x3)
#define DISABLE_TIETEN    ~(0x3)
#define DISABLE_TIF    ~(0x1)

void PIT0_IRQHandler(){

	PIT->CHANNEL[PIT_0].TCTRL &= DISABLE_TIETEN;
	PIT->CHANNEL[PIT_0].TFLG  &= DISABLE_TIF;
}

void PIT_clockGating(){

	SIM->SCGC6 |= PIT_CLOCK_GATING;
}


uint8 PIT_interruptFlagStatus(PIT_Timer_t pitTimer){

	return (PIT->CHANNEL[pitTimer].TFLG);

}
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float perior){
	PIT->MCR = ENABLE;
	float tiempo=(( systemClock*perior)/2.0F);

	PIT->CHANNEL[pitTimer].LDVAL=tiempo;
	PIT->CHANNEL[pitTimer].TFLG |= PIT_TFLG_TIF_MASK;
	PIT->CHANNEL[pitTimer].TCTRL|= (PIT_TCTRL_TIE_MASK);//enables PIT timer interrupt
	PIT->CHANNEL[pitTimer].TCTRL |= (PIT_TCTRL_TEN_MASK);//enables timer0


}

uint8 PIT_getIntrStatus(PIT_Timer_t pitTimer){
	return (PIT->CHANNEL[pitTimer].CVAL);

}


void PIT_clear(PIT_Timer_t pitTimer){

}
