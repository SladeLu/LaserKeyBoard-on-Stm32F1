#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "lcd.h"	  
#include "ov7670.h"
#include "usmart.h"  
#include "KeyInfo.h"
   
//Mini STM32������
	  
#define SIG_MAX 10	  //ƽ�����

extern u8 ov_sta;	//��exit.c���涨��
extern u8 ov_frame;	//��timer.c���涨��	
	 
//����LCD��ʾ

void camera_refresh(void)
{
	u32 j,i,sigma;
 	u16 color;	 
	u16 R,G,B;
	u32 first_x = 0;
	u32 first_y = 0;
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//���ϵ���,������ 
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	
 		OV7670_CS=0;	 
 		OV7670_RRST=0;				//��ʼ��λ��ָ�� 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//��λ��ָ����� 
		OV7670_RCK=1;
		sigma = 0; 
		for(i=0;i<240;i++)
		{
		 
			for(j=0;j<320;j++)        /*********************/
			{
			GPIOB->CRL=0X88888888;		   
			OV7670_RCK=0; 
			color=OV7670_DATA;		//������
			OV7670_RCK=1; 	
			color<<=8;					  
 			OV7670_RCK=0;
			color|=OV7670_DATA;		//������		  
			OV7670_RCK=1; 
			GPIOB->CRL=0X33333333;	
		
			R = (u16)GETR_FROM_RGB16(color);
			G = (u16)GETG_FROM_RGB16(color);
			B = (u16)GETB_FROM_RGB16(color);	

           if((R>=238)&&(G>=238)&&(B>=238))
			{
				color = WHITE;
				sigma++;
			}
			else
			{
				color =BLACK;
			}  		  
			if(sigma==SIG_MAX)
			{
				first_x = j;
				first_y = i;
			}
			/*if(i==120)
			{
				color = WHITE;
			}
			else
			{
				color =BLACK;
			}*/
				LCD_WriteRAM(color);
			}	
		}
		Judgement_Test(first_x,first_y);
 		OV7670_CS=1; 							 
		OV7670_RCK=0; 
		OV7670_RCK=1; 
		EXTI->PR=1<<15;     		//���LINE8�ϵ��жϱ�־λ
		ov_sta=0;					//��ʼ��һ�βɼ�
 		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//�ָ�Ĭ��ɨ�跽�� 	  				 	 
	} 
}	  


int main(void)
{	
	u8 i;	
   	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
  	OV7670_Init();				  
	printf("SUCCESS");
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KeyBoard_Init();		//��ʼ�������������
	LCD_Init();			   	//��ʼ��LCD
	if(lcddev.id==0X6804) 	//ǿ��������Ļ�ֱ���Ϊ320*240.��֧��3.5�����
	{
		lcddev.width=240;
		lcddev.height=320; 
	}
	usmart_dev.init(72);	//��ʼ��USMART		
 			    
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,200,16,"Mini STM32");	
	LCD_ShowString(60,70,200,200,16,"OV7670 TEST");	
	  	 
	LCD_ShowString(60,130,200,200,16,"Use USMART To Set!");	 
  	LCD_ShowString(60,150,200,200,16,"OV7670 Init...");	  
	while(OV7670_Init())//��ʼ��OV7670
	{
		LCD_ShowString(60,150,200,200,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,150,200,200,16,"OV7670 Init OK");
	delay_ms(1500);	 	   	  
	Timerx_Init(10000,7199);			//TIM3,10Khz����Ƶ��,1�����ж�									  
	EXTI15_Init();						//ʹ�ܶ�ʱ������
	OV7670_Window_Set(10,174,240,320);	//���ô���	  
  OV7670_CS=0;						 	 
 	while(1)
	{	
 		camera_refresh();	//������ʾ	 
 		if(i!=ov_frame)		//DS0��˸.
		{
			i=ov_frame;
			LED0=!LED0;
 		}
	}	   
}















