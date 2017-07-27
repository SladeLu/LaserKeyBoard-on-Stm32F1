#ifndef	__MAIN_H_
#define __MAIN_H_

#include "stm32f4xx.h"

#define EN_PERIPH_FUNC					1


#include "struct.h"

#if EN_PERIPH_FUNC
/************************		  include some basic peripheral .h file		******************/
#include "main_init.h"

#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "ascii.h"
#include "usart.h"
#include "flash_spi.h"
#include "touch.h"
#include "touch_spi.h"
#include "key.h"

#include "ov7725.h"
#include "sccb.h"
#include "ov7725_proc.h"
#endif
/***************************************************************************************/

/*********************				Quote C Default Lib					******************************/
#include <math.h>
#include <stdio.h>
/***************************************************************************************/

/************************				Quote variables 		************************************/
//三种字体的格式
extern FONT Font16x24;
extern FONT Font8x16;
extern FONT Font6x12;
extern long double cal_p[6];				//触摸屏校正系数结构体
/********************************************************************************/


#endif
