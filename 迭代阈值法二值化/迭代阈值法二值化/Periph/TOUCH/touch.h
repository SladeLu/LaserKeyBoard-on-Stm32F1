#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "main.h"
#include "struct.h"




	 
#define TCS_LOW    			GPIO_ResetBits(GPIOB, GPIO_Pin_12)		//XPT2046Ƭѡ�˿��õ�
#define TCS_HIGH   			GPIO_SetBits(GPIOB, GPIO_Pin_12)      //XPT2046Ƭѡ�˿��ø�
#define INT_IN_2046()		(GPIOG->IDR&GPIO_Pin_7)								//��ȡ����������״̬  0---����  1---δ����

#define CHY 0X90  			//ͨ��Y+��ѡ�������
#define CHX 0XD0    		//ͨ��Z+��ѡ�������									 	    

//��������
void Touch_Init(void);		 		 
u16 ADS_Read(u8 CMD);	 
u16 Read_XY(u8 CMD);
Coordinate *Read_2046_2(void);
int Touch_Calibrate(u8 cal_flag);
FunctionalState Get_touch_point(Coordinate * displayPtr,Coordinate * screenPtr);
	 
#endif


