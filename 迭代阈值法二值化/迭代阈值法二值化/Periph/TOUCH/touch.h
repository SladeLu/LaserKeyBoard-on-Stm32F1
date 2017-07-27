#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "main.h"
#include "struct.h"




	 
#define TCS_LOW    			GPIO_ResetBits(GPIOB, GPIO_Pin_12)		//XPT2046片选端口置低
#define TCS_HIGH   			GPIO_SetBits(GPIOB, GPIO_Pin_12)      //XPT2046片选端口置高
#define INT_IN_2046()		(GPIOG->IDR&GPIO_Pin_7)								//读取触摸屏引脚状态  0---触摸  1---未触摸

#define CHY 0X90  			//通道Y+的选择控制字
#define CHX 0XD0    		//通道Z+的选择控制字									 	    

//函数声明
void Touch_Init(void);		 		 
u16 ADS_Read(u8 CMD);	 
u16 Read_XY(u8 CMD);
Coordinate *Read_2046_2(void);
int Touch_Calibrate(u8 cal_flag);
FunctionalState Get_touch_point(Coordinate * displayPtr,Coordinate * screenPtr);
	 
#endif


