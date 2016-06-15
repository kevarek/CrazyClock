/*
 * mygpio.c
 *
 *  Created on: 24.12.2012
 *      Author: Standa
 */
#include "LPC11Uxx.h"                         //LPC11xx definitions
#include "gpio.h"
#include "mygpio.h"

void mygpio_init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 6); /* Enable AHB clock to the GPIO domain. */
	//configure pins as output
	GPIOSetDir( 0, LEDPIN, 1 );
	GPIOSetDir( PORT, PINBLUE, 1 );
	GPIOSetDir( PORT, PINYELLOW, 1 );
	//set pin values to zero
	GPIOSetBitValue( 0, LEDPIN, 0 );
	GPIOSetBitValue( PORT, PINBLUE, 0 );
	GPIOSetBitValue( PORT, PINYELLOW, 0 );
}


void mygpio_pinblue_set(void){
	GPIOSetBitValue( PORT, PINBLUE, 1 );
}

void mygpio_pinblue_clear(void){
	GPIOSetBitValue( PORT, PINBLUE, 0 );
}

void mygpio_pinyellow_set(void){
	GPIOSetBitValue( PORT, PINYELLOW, 1 );
}

void mygpio_pinyellow_clear(void){
	GPIOSetBitValue( PORT, PINYELLOW, 0 );
}

void mygpio_ledpin_set(void){
	GPIOSetBitValue( 0, LEDPIN, 1 );
}

void mygpio_ledpin_clear(void){
	GPIOSetBitValue( 0, LEDPIN, 0 );
}
