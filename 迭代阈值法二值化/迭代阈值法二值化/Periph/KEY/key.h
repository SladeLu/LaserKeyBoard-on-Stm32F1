#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f4xx.h"

/*		定义按键端口	*/
#define RCC_KEY		RCC_AHB1Periph_GPIOF
#define KEY_PORT	GPIOF
#define KEY_PIN		GPIO_Pin_11
//读取按键的状态值
#define KEY_VAL GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN)

//函数声明
void KEY_Init(void);
char Key_Scan(uint8_t mode);

#endif