#include "ov7725_proc.h"


#define PIXEL_W      320
#define PIXEL_H      150
#define PIXEL_BREAK  100

//灰度直方图数值，用来判断按图像质量
u32 gray_test_value[26];   //像素点数数据
u8 gray_test_send[28];     //发送给上位机的数据

//阈值分割灰度图
u8 gray_itera_threshold[256];
u16 threshold_h[256];
#define GRAY_BREAK_RANGE     1    //阈值允许参数

static u8 pixel[PIXEL_H][PIXEL_W];


/*       320
 * -------------------
 *|                   |
 *|                   |
 *|                   |  240
 *|                   |
 *|                   |
 * -------------------
 */
void ImagDisp(void)
{
	uint16_t i=0, j=0;
	uint16_t Camera_Data;
	uint16_t R,G,B,mux,mux_later;
	float data = 0.0;

	LCD_SetCursor(0,0);
	LCD_WriteIndex(0x22);					//准备写入数据
	
	for(i = 0; i<PIXEL_H; i++)
	{
		for(j = 0; j<PIXEL_W; j++)
		{
			READ_FIFO_PIXEL(Camera_Data);		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */
		 //转换成灰度图			
			R = (uint16_t)GETR_FROM_RGB16(Camera_Data);
			G = (uint16_t)GETG_FROM_RGB16(Camera_Data);
			B = (uint16_t)GETB_FROM_RGB16(Camera_Data);
			mux = (R*30+G*59+B*11)/100;
//			mux = G;
      
			pixel[i][j] = mux;
			
//      pixel[i][j] = GETGRAY_FROM_RGB16(R,G,B);
//			
//			mux = pixel[i][j];
//			Camera_Data =  GRAY_TO_RGB(mux);
      LCD_WriteData(Camera_Data);
		}

	}
}



/*********************************************************
* 函数名：ov7725_capanddisp
* 功  能：摄像头捕获并且显示
*********************************************************/
void ov7725_capanddisp(void)
{
	u16 i=0,j=0;
	u16 mux=0,Camera_Data=0;
	u8 gray_cnt=0;
	

	if( Ov7725_vsync == 2 )
	{
		FIFO_PREPARE;  			/*FIFO准备*/					
		ImagDisp();					/*采集并显示*/
		Ov7725_vsync = 0;
    
//		//迭代阈值分割图像
//		Itera_Threshold();
//		while(1);
		//串口发送数据在PC机上显示灰度直方图
//		OV7725_GRAY_Serial();
		
	}
}

/*************************************************************
* 函数名：OV7725_GRAY_Serial
* 功  能：摄像头发送灰度图到上位机分析
*************************************************************/
void OV7725_GRAY_Serial(void)
{
  u16 i=0,j=0,mux=0;
	
	//数据清空
	for( i=0; i<28; i++ )
	{
	  gray_test_value[i] = 0;
	}
	

	for(i = 0; i<PIXEL_H; i++)
	{
		for(j = 0; j<PIXEL_W; j++)
		{
			mux = pixel[i][j];
			
			//像素点数自增       
			gray_test_value[mux/6]++;
		}
	}

	for( i=0; i<26; i++ )
	{
		gray_test_send[i+1] = gray_test_value[i]/320;
		gray_test_value[i] = 0;
	}
	gray_test_send[0] = 0xFA;    //帧头
	gray_test_send[27] = 0xFF;   //帧尾
	for( i=0; i<28; i++ )
	{
		printf("%c",gray_test_send[i]);
	}
}


/****************************************************
* 函数名：Itera_Threshold
* 功  能：迭代阈值法，能够找到灰度图的最佳二值化点
****************************************************/
void Itera_Threshold(void)
{
  u16 i=0,j=0,k=0,cnt=0,mux=0,Camera_Data=0;
	u8 newthreshold=0;
	u16 Pmax=0,Pmin=0;
	u32 sum_h1=0,sum_h2=0;
	
	
	//数据清空
	for( i=0; i<256; i++ )
	{
	  gray_test_value[i] = 0;
	}
	
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //获取灰度图的数据
		
			//像素点数自增       
			gray_itera_threshold[mux]++;	
		}
	}
	
	Pmin = gray_itera_threshold[0];
	Pmax = gray_itera_threshold[0];
	for( cnt=0; cnt<256; cnt++ )
	{
	  if( Pmin>gray_itera_threshold[cnt] ){
		  Pmin = gray_itera_threshold[cnt];
		}
		if( Pmax<gray_itera_threshold[cnt] ){
		  Pmax = gray_itera_threshold[cnt];
		}
	}
	
	printf("the Pmax is %d\n",Pmax);
	printf("the Pmin is %d\n",Pmin);
	
	//初始阈值
	threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//寻找最佳阈值
	for( k=0; k<256; k++ )
	{
		//分割前景和背景
		for( cnt=0; cnt<threshold_h[k]; cnt++ )
		{
			sum_h1 += gray_itera_threshold[cnt];
		}
		for( cnt=threshold_h[k]; cnt<256; cnt++ )
		{
			sum_h2 += gray_itera_threshold[cnt];
		}
		sum_h1 /= threshold_h[k];
		sum_h2 /= (256-threshold_h[k]);
		
		//计算出新的阈值
		threshold_h[k+1] = ( sum_h1 + sum_h2 ) / 2; 
		
		if( fabs(threshold_h[k]-threshold_h[k+1]) <= GRAY_BREAK_RANGE ){
			newthreshold = threshold_h[k+1];
		  break;
		}
		
		sum_h1 = 0;
		sum_h2 = 0;
	}

	printf("the newthreshold is %d\n",newthreshold);
	
	//在液晶屏上面写入图像分割后的图像
  LCD_SetCursor(0,0);
	LCD_WriteIndex(0x22);					//准备写入数据
	//根据最佳阈值将图像二值化
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //获取灰度图的数据
		  //图像二值化
			if( mux > newthreshold ){
			  mux = 255;
			}
			else{
			  mux = 0;
			}
			
			Camera_Data =  GRAY_TO_RGB(mux);
      LCD_WriteData(Camera_Data);
			
		}
	}
	

	
}
