/*
 * ee338.c
 *
 *  Created on: 23.12.2012
 *      Author: Standa
 */
#include "ee338.h"

#include "LPC11Uxx.h"                        /* LPC11xx definitions */
#include "mygpio.h"
#include "mytimer.h"




void ee338_init(void){
	mytimer_init();
	mygpio_init();
}

void ee338_movefw(void){
	mytimer1_mywaitmsint(40);
	mygpio_ledpin_set();
	if(dir){
		mygpio_pinblue_clear();
		mygpio_pinyellow_set();
		dir=0;
	}
	else{
		mygpio_pinblue_set();
		mygpio_pinyellow_clear();
		dir=1;
	}
	__WFI();

	mytimer1_mywaitmsint(1);
	if(!dir){
		mygpio_pinblue_clear();
		mygpio_pinyellow_set();
	}
	else{
		mygpio_pinblue_set();
		mygpio_pinyellow_clear();
	}

	__WFI();
	mygpio_pinblue_clear();
	mygpio_pinyellow_clear();
	mygpio_ledpin_clear();
}

void ee338_movebw(void){
	mytimer1_mywaitmsint(15);
	mygpio_ledpin_set();
	if(dir){
		mygpio_pinblue_clear();
		mygpio_pinyellow_set();
		dir=0;
	}
	else{
		mygpio_pinblue_set();
		mygpio_pinyellow_clear();
		dir=1;
	}
	__WFI();

	mytimer1_mywaitmsint(40);
	if(dir){
		mygpio_pinblue_clear();
		mygpio_pinyellow_set();
	}
	else{
		mygpio_pinblue_set();
		mygpio_pinyellow_clear();
	}
	__WFI();

	if(!dir){

		mygpio_pinblue_set();
		mygpio_pinyellow_clear();
	}
	else{
		mygpio_pinblue_clear();
		mygpio_pinyellow_set();
	}
	mygpio_pinblue_clear();
	mygpio_pinyellow_clear();
	mygpio_ledpin_clear();
}
