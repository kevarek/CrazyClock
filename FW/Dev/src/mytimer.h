/*
 * mytimer.h
 *
 *  Created on: 24.12.2012
 *      Author: Standa
 */

#ifndef MYTIMER_H_
#define MYTIMER_H_

extern volatile int dir;
extern void (*volatile tmr1_irqh_ptr)(void);

extern void mytimer_init(void);
extern void mytimer0_mywaitmsint(int);
extern void mytimer1_mywaitmsint(int);

extern void tmr1_irqh_fw(void);
extern void tmr1_irqh_bw_pulse(void);


#endif /* MYTIMER_H_ */
