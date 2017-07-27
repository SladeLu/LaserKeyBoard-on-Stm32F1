#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f4xx.h"

/*		���尴���˿�	*/
#define RCC_KEY		RCC_AHB1Periph_GPIOF
#define KEY_PORT	GPIOF
#define KEY_PIN		GPIO_Pin_11
//��ȡ������״ֵ̬
#define KEY_VAL GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN)

//��������
void KEY_Init(void);
char Key_Scan(uint8_t mode);

#endif