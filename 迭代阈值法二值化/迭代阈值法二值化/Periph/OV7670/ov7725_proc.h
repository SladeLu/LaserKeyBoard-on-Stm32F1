#ifndef	__OV7725_PROC_H_
#define __OV7725_PROC_H_

#include "main.h"

#define CAMERA_W  320
#define CAMERA_H  240


//#define CAMERA_DEBUG

#define GRAY_TEST


#define GRAY_TO_RGB(MUX)         ((MUX>>3<<11)|(MUX>>2<<5)|(MUX>>3))

//��ȡ��ɫ���ֽ�ֵ
#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//����8λ R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//����8λ G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//����8λ B

//#define GETGRAY_FROM_RGB16(R,G,B)  ((unsigned char)((R<<5+G<<8+B<<3)>>7))
#define GETGRAY_FROM_RGB16(RGB565)  ((unsigned char)( (((RGB565>>11)<<8)+((RGB565&0x7FF)<<5)+((RGB565&0x1F)<<7))>>7 ))
//#define GETGRAY_FROM_RGB16(RGB565)  ((unsigned char)( ((RGB565*0.1172)+((RGB565&0x7FF)*3.6875)+((RGB565&0x1F)*88))/100 ))

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������																		
void ImagDisp(void);			
void ov7725_capanddisp(void);			//ov7725�ɼ�������ʾ																
void Itera_Threshold(void);

//��λ����ʾ�Ҷ�ֱ��ͼ����
void OV7725_GRAY_Serial(void);

#endif