#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" 

#define ON  0
#define OFF 1

void ledInit(void);
void led0(u8 t);    //ºìÉ«LED
void led1(u8 t);		//ÂÌÉ«LED

#endif
