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
   
//Mini STM32开发板
	  
#define SIG_MAX 10	  //平衡误差

extern u8 ov_sta;	//在exit.c里面定义
extern u8 ov_frame;	//在timer.c里面定义	
	 
//更新LCD显示

void camera_refresh(void)
{
	u32 j,i,sigma;
 	u16 color;	 
	u16 R,G,B;
	u32 first_x = 0;
	u32 first_y = 0;
	if(ov_sta==2)
	{
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右 
		LCD_SetCursor(0x00,0x0000);	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
 		OV7670_CS=0;	 
 		OV7670_RRST=0;				//开始复位读指针 
		OV7670_RCK=0;
		OV7670_RCK=1;
		OV7670_RCK=0;
		OV7670_RRST=1;				//复位读指针结束 
		OV7670_RCK=1;
		sigma = 0; 
		for(i=0;i<240;i++)
		{
		 
			for(j=0;j<320;j++)        /*********************/
			{
			GPIOB->CRL=0X88888888;		   
			OV7670_RCK=0; 
			color=OV7670_DATA;		//读数据
			OV7670_RCK=1; 	
			color<<=8;					  
 			OV7670_RCK=0;
			color|=OV7670_DATA;		//读数据		  
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
		EXTI->PR=1<<15;     		//清除LINE8上的中断标志位
		ov_sta=0;					//开始下一次采集
 		ov_frame++; 
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向 	  				 	 
	} 
}	  


int main(void)
{	
	u8 i;	
   	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
  	OV7670_Init();				  
	printf("SUCCESS");
	LED_Init();		  		//初始化与LED连接的硬件接口
	KeyBoard_Init();		//初始化激光键盘外设
	LCD_Init();			   	//初始化LCD
	if(lcddev.id==0X6804) 	//强制设置屏幕分辨率为320*240.以支持3.5寸大屏
	{
		lcddev.width=240;
		lcddev.height=320; 
	}
	usmart_dev.init(72);	//初始化USMART		
 			    
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,200,16,"Mini STM32");	
	LCD_ShowString(60,70,200,200,16,"OV7670 TEST");	
	  	 
	LCD_ShowString(60,130,200,200,16,"Use USMART To Set!");	 
  	LCD_ShowString(60,150,200,200,16,"OV7670 Init...");	  
	while(OV7670_Init())//初始化OV7670
	{
		LCD_ShowString(60,150,200,200,16,"OV7670 Error!!");
		delay_ms(200);
	    LCD_Fill(60,230,239,246,WHITE);
		delay_ms(200);
	}
 	LCD_ShowString(60,150,200,200,16,"OV7670 Init OK");
	delay_ms(1500);	 	   	  
	Timerx_Init(10000,7199);			//TIM3,10Khz计数频率,1秒钟中断									  
	EXTI15_Init();						//使能定时器捕获
	OV7670_Window_Set(10,174,240,320);	//设置窗口	  
  OV7670_CS=0;						 	 
 	while(1)
	{	
 		camera_refresh();	//更新显示	 
 		if(i!=ov_frame)		//DS0闪烁.
		{
			i=ov_frame;
			LED0=!LED0;
 		}
	}	   
}















