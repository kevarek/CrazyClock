/*
 * mygpio.h
 *
 *  Created on: 24.12.2012
 *      Author: Standa
 */

#ifndef MYGPIO_H_
#define MYGPIO_H_

#define PORT	1
#define PINBLUE		20
#define PINYELLOW	21

#define LEDPIN		7


extern void mygpio_pinblue_set(void);
extern void mygpio_pinblue_clear(void);
extern void mygpio_pinyellow_set(void);
extern void mygpio_pinyellow_clear(void);
extern void mygpio_ledpin_set(void);
extern void mygpio_ledpin_clear(void);

extern void mygpio_init(void);


#endif /* MYGPIO_H_ */
