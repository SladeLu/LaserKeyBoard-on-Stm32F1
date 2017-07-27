#include "ov7725_proc.h"


#define PIXEL_W      320
#define PIXEL_H      150
#define PIXEL_BREAK  100

//�Ҷ�ֱ��ͼ��ֵ�������жϰ�ͼ������
u32 gray_test_value[26];   //���ص�������
u8 gray_test_send[28];     //���͸���λ��������

//��ֵ�ָ�Ҷ�ͼ
u8 gray_itera_threshold[256];
u16 threshold_h[256];
#define GRAY_BREAK_RANGE     1    //��ֵ�������

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
	LCD_WriteIndex(0x22);					//׼��д������
	
	for(i = 0; i<PIXEL_H; i++)
	{
		for(j = 0; j<PIXEL_W; j++)
		{
			READ_FIFO_PIXEL(Camera_Data);		/* ��FIFO����һ��rgb565���ص�Camera_Data���� */
		 //ת���ɻҶ�ͼ			
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
* ��������ov7725_capanddisp
* ��  �ܣ�����ͷ��������ʾ
*********************************************************/
void ov7725_capanddisp(void)
{
	u16 i=0,j=0;
	u16 mux=0,Camera_Data=0;
	u8 gray_cnt=0;
	

	if( Ov7725_vsync == 2 )
	{
		FIFO_PREPARE;  			/*FIFO׼��*/					
		ImagDisp();					/*�ɼ�����ʾ*/
		Ov7725_vsync = 0;
    
//		//������ֵ�ָ�ͼ��
//		Itera_Threshold();
//		while(1);
		//���ڷ���������PC������ʾ�Ҷ�ֱ��ͼ
//		OV7725_GRAY_Serial();
		
	}
}

/*************************************************************
* ��������OV7725_GRAY_Serial
* ��  �ܣ�����ͷ���ͻҶ�ͼ����λ������
*************************************************************/
void OV7725_GRAY_Serial(void)
{
  u16 i=0,j=0,mux=0;
	
	//�������
	for( i=0; i<28; i++ )
	{
	  gray_test_value[i] = 0;
	}
	

	for(i = 0; i<PIXEL_H; i++)
	{
		for(j = 0; j<PIXEL_W; j++)
		{
			mux = pixel[i][j];
			
			//���ص�������       
			gray_test_value[mux/6]++;
		}
	}

	for( i=0; i<26; i++ )
	{
		gray_test_send[i+1] = gray_test_value[i]/320;
		gray_test_value[i] = 0;
	}
	gray_test_send[0] = 0xFA;    //֡ͷ
	gray_test_send[27] = 0xFF;   //֡β
	for( i=0; i<28; i++ )
	{
		printf("%c",gray_test_send[i]);
	}
}


/****************************************************
* ��������Itera_Threshold
* ��  �ܣ�������ֵ�����ܹ��ҵ��Ҷ�ͼ����Ѷ�ֵ����
****************************************************/
void Itera_Threshold(void)
{
  u16 i=0,j=0,k=0,cnt=0,mux=0,Camera_Data=0;
	u8 newthreshold=0;
	u16 Pmax=0,Pmin=0;
	u32 sum_h1=0,sum_h2=0;
	
	
	//�������
	for( i=0; i<256; i++ )
	{
	  gray_test_value[i] = 0;
	}
	
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //��ȡ�Ҷ�ͼ������
		
			//���ص�������       
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
	
	//��ʼ��ֵ
	threshold_h[0] = ( Pmax + Pmin ) / 2;
	
	//Ѱ�������ֵ
	for( k=0; k<256; k++ )
	{
		//�ָ�ǰ���ͱ���
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
		
		//������µ���ֵ
		threshold_h[k+1] = ( sum_h1 + sum_h2 ) / 2; 
		
		if( fabs(threshold_h[k]-threshold_h[k+1]) <= GRAY_BREAK_RANGE ){
			newthreshold = threshold_h[k+1];
		  break;
		}
		
		sum_h1 = 0;
		sum_h2 = 0;
	}

	printf("the newthreshold is %d\n",newthreshold);
	
	//��Һ��������д��ͼ��ָ���ͼ��
  LCD_SetCursor(0,0);
	LCD_WriteIndex(0x22);					//׼��д������
	//���������ֵ��ͼ���ֵ��
	for( i=0; i<PIXEL_H; i++ )
	{
	  for( j=0; j<PIXEL_W; j++ )
		{
		  mux = pixel[i][j];                     //��ȡ�Ҷ�ͼ������
		  //ͼ���ֵ��
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
