#ifndef	__DELAY_H_
#define __DELAY_H_

#include "stm32f4xx.h"

//º¯ÊıÉùÃ÷
void Delay_Init(uint8_t SYSCLK);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif