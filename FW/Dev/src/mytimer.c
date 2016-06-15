/*
 * mytimer.c
 *
 *  Created on: 24.12.2012
 *      Author: Standa
 */

#include "LPC11Uxx.h"                         //LPC11xx definitions
#include "timer32.h"
#include "gpio.h"

#include "mytimer.h"
#include "mygpio.h"


volatile int dir=0;
void (*volatile tmr1_irqh_ptr)(void);


////////////////////////
////TIMER0 FUNCTIONS////
////////////////////////
void mytimer0_init(void) {
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9); //enable peripheral clock

	LPC_CT32B0->TCR = 0x02; /* reset timer */
	LPC_CT32B0->PR = 0x00; /* set prescaler to zero */
	LPC_CT32B0->MCR = 0x07; /* stop and reset timer on match, generate interrupt*/
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	LPC_CT32B0->IR = 0xff; /* reset all  t0 interrrupts */
}

void mytimer0_mywaitmsint(int ms) {
	LPC_CT32B0->TCR = 0x02; /* reset timer */
	LPC_CT32B0->MR0 =(SystemCoreClock / 1000)*ms;
	LPC_CT32B0->TCR = 0x01; /* start timer */
}

void TIMER32_0_IRQHandler(void){
	LPC_CT32B0->IR  = 0xff;		/* reset all t0 interrupts */
}


////////////////////////
////TIMER1 FUNCTIONS////
////////////////////////

void mytimer1_init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 10); //enable peripheral clock
	LPC_CT32B1->TCR = 0x02; /* reset timer */
	LPC_CT32B1->PR = 0x00; /* set prescaler to zero */
	LPC_CT32B1->MCR = 0x07; /* stop and reset timer on match, generate interrupt*/
	NVIC_EnableIRQ(TIMER_32_1_IRQn);
	LPC_CT32B1->IR = 0xff; /* reset all  t1 interrrupts */
}

void mytimer1_mywaitmsint(int ms) {
	LPC_CT32B1->TCR = 0x02; /* reset timer */
	LPC_CT32B1->MR0 = ms * (SystemCoreClock / 1000);
	LPC_CT32B1->IR = 0xff; /* reset all  t1 interrrupts */
	LPC_CT32B1->TCR = 0x01; /* start timer */
}

void TIMER32_1_IRQHandler(void){
	LPC_CT32B1->IR  = 0xff;		/* reset all t1 interrupts */
}

void mytimer_init(void){
	mytimer0_init();
	mytimer1_init();
}
