/*
 * myadc.c
 *
 *  Created on: 25.12.2012
 *      Author: Standa
 */

#include "LPC11Uxx.h"                         //LPC11xx definitions
#include "myadc.h"
#include "adc.h"


int myadc_getrandomseed(void){
	int i,tmp,seed;
	ADCInit(1000000);
	for(i=0;i<8;i++){

		tmp=ADCRead(i);
		tmp&=0x7;	//three bits
		seed|=(tmp<<(i*3));
	}
	ADCDeinit();
	seed=seed;
	return seed;
}

