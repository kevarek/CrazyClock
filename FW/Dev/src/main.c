/*
 * main.c
 *
 *  Created on: 23.12.2012
 *      Author: Standa
 */

#include "LPC11Uxx.h"
#include "crazyclock.h"

/* Main Program */
int main(void) {
	SystemCoreClockUpdate(); //initialize mcu clocks
	cc_init();
	while (1) {
		cc_prepnexttick();	//as soon as possible prepare next tick -> minimize delay
		cc_tick();			//do tick
		__WFI();			//wait for interrupt
	}
}
