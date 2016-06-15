/*
 * crazyclock.c
 *
 *  Created on: 23.12.2012
 *      Author: Standa
 */

#include "crazyclock.h"
#include "LPC11Uxx.h"                        /* LPC11xx definitions */
#include "ee338.h"
#include "mygpio.h"
#include "mytimer.h"
#include "myadc.h"

#include <stdlib.h>

#define MAXTIMEDIFFERENCE	20000		//in ms

#define DELTAMIN			-650		//in ms
#define DELTAMAX			650			//in ms
#define TMAX				15
#define TMIN				5

#define MOD_NORMAL_PROB		10			//in perc
#define MOD_RANDOM_PROB		30			//in perc
//#define MOD_CONTINUOUS_PROB	- calculated from previous to 100%


typedef struct{
	int current;
	int items;
	int buffer[200];
} cc_bufferstruct;

typedef struct{
	int tmin;
	int tmax;
	int deltamin;
	int deltamax;
	int delay;
	int clockwise;
	cc_bufferstruct *abuffer;
	cc_bufferstruct *wbuffer;
} cc_statusstruct;

static cc_bufferstruct a,b;
static cc_statusstruct status={	TMIN,
								TMAX,
								DELTAMIN,
								DELTAMAX,
								-24500,
								1,
								&a,
								&b
};


void cc_randomizewaitingbuffer(void){
	int starttime=0,
		startdelta=status.abuffer->buffer[status.abuffer->items-1],
		endtime=status.tmin+(rand()%(status.tmax-status.tmin)),
		enddelta=status.deltamin+rand()%(status.deltamax-status.deltamin),	//rand in range dmin-dmax
		ticks=endtime-starttime,
		k=(enddelta-startdelta)/(endtime-starttime),
		i,
		delta,
		roll;

	status.wbuffer->items=ticks;
	status.wbuffer->current=0;

	if(status.delay<-MAXTIMEDIFFERENCE){
/*		for(i=0;i<ticks;i++){
			status.wbuffer->buffer[i]=status.deltamax;
		}*/
		roll=rand()%7;		//0...6
		status.wbuffer->items=10+roll;

		status.wbuffer->buffer[0]=-300;
		status.wbuffer->buffer[1]=-250;
		status.wbuffer->buffer[2]=-200;
		status.wbuffer->buffer[3]=-150;
		status.wbuffer->buffer[4]=-150;
		status.wbuffer->buffer[5]=0;
		status.wbuffer->buffer[6]=400;
		status.wbuffer->buffer[7]=800;
		status.wbuffer->buffer[8]=1300;
		status.wbuffer->buffer[9]=-2500;
		status.wbuffer->buffer[10]=-2200;	//6
		status.wbuffer->buffer[11]=-2000;
		status.wbuffer->buffer[12]=-1800;
		status.wbuffer->buffer[13]=-1700;
		status.wbuffer->buffer[14]=-1900;
		status.wbuffer->buffer[15]=-2500;
		status.wbuffer->buffer[16]=-2800;

	}
	else if(status.delay>MAXTIMEDIFFERENCE){
		for(i=0;i<ticks;i++){
			status.wbuffer->buffer[i]=status.deltamin;
		}
	}
	else{
		roll=rand()%100;
		if(roll<MOD_RANDOM_PROB){	//mod random
			for(i=0;i<ticks;i++){
				delta=status.deltamin+rand()%(status.deltamax-status.deltamin),	//rand in range dmin-dmax
				status.wbuffer->buffer[i]=delta;
			}

		}
		else if(roll>(100-MOD_NORMAL_PROB)){	//mod normal
			status.wbuffer->buffer[i]=0;
		}
		else{			//mod continuous
			for(i=0;i<ticks;i++){
				delta=startdelta+k*i;
				if(delta<=status.deltamin) delta=status.deltamin;
				else if (delta>=status.deltamax) delta=status.deltamax;
				status.wbuffer->buffer[i]=delta;
			}
		}
	}
}

void cc_initializebuffers(void){
	//initialize active buffer first
	int starttime=0,
		startdelta=0,
		endtime=status.tmin+(rand()%(status.tmax-status.tmin)),
		enddelta=status.deltamin+rand()%(status.deltamax-status.deltamin),	//rand in range dmin-dmax
		ticks=endtime-starttime,
		k=(enddelta-startdelta)/(endtime-starttime),
		i,
		delta;

	status.abuffer->items=ticks;
	status.abuffer->current=0;
	for(i=0;i<ticks;i++){
		delta=startdelta+k*i;
		status.abuffer->buffer[i]=delta;
	}
	//then initialize waiting buffer
	cc_randomizewaitingbuffer();
}



void cc_tick(void){
	if(status.clockwise) ee338_movefw();
	else ee338_movebw();

}

void cc_switchbuffers(void){
	cc_bufferstruct *tmp;
	//switch active and waiting buffers
	tmp=status.abuffer;
	status.abuffer=status.wbuffer;
	status.wbuffer=tmp;
}

void cc_prepnexttick(void){
	int delta=status.abuffer->buffer[status.abuffer->current],
		timeval=1000+delta;

	if(timeval>0){
		mytimer0_mywaitmsint(timeval);	//set interrupt for next tick
		status.delay+=delta;
		status.clockwise=1;
	}
	else{
		mytimer0_mywaitmsint(-1*timeval);	//set interrupt for next tick
		status.delay-=delta;
		status.clockwise=0;
	}

	status.abuffer->current++;	//increment current delay indicator
	if(status.abuffer->current>status.abuffer->items-1){	//if indicator is bigger then number of items in buffer
		cc_switchbuffers();
		cc_randomizewaitingbuffer();		//fill new waiting buffer with randomized data
	}


}


void cc_init(void){
	mygpio_init();
	mytimer_init();
	ee338_init();
	srand(myadc_getrandomseed());

	cc_initializebuffers();
}
