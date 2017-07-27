#ifndef	__LED_H_
#define __LED_H_

#include "stm32f4xx.h"

/*  对寄存器控制 */
#define digitalHi(p,i)						{p->BSRRL = i;}
#define digitalLo(p,i)						{p->BSRRH = i;}
#define digitalToggle(p,i)				{p->ODR ^= i;}

#define LED_ON										digitalLo(GPIOB,GPIO_Pin_0)
#define LED_OFF										digitalHi(GPIOB,GPIO_Pin_0)
#define LED_TOGGLE								digitalToggle(GPIOB,GPIO_Pin_0)

//函数声明
void LED_Init(void);

#endif