#ifndef	__LCD_H_
#define __LCD_H_

#include "main.h"
#include "struct.h"

/*
* ˵  ����DISP_MODE --- ѡ����ʾ����
					1  --- ����->���� ����
					2  --- ����->���� ����
					3  --- ����->���� ����
					4  --- ����->���� ����
*/
#define DISP_MODE 2

/*			������Ļ��С			*/
#define WEIGH			320
#define HIGH			240

//��ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			 			 0XFFE0
#define GBLUE			 			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 //��ɫ
#define BRRED 			 		 0XFC07 //�غ�ɫ
#define GRAY  			 		 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ

#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
#define LCD         ((LCD_TypeDef *) LCD_BASE)

#define LCD_WriteIndex(index) 				LCD->LCD_REG=index
#define LCD_WriteData(data)						LCD->LCD_RAM=data


//��������
void LCDILI9325_Init();
void LCD_SetCursor(u16 x,u16 y);
void LCD_SetWindows(u16 startx,u16 starty,u16 endx,u16 endy);
void LCD_Clear(u16 color);
u16 LCD_GetPoint(u16 x,u16 y);
void LCD_SetPoint(u16 x,u16 y,u16 point);

/**********************					Ӧ�ú���					********************************/
void LCD_DrawPicture(u16 startx,u16 starty,u16 endx,u16 endy,u16 *pic);
void LCD_Fill(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 color);
void LCD_Rect(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 color);
void LCD_Circle(u16 xpos,u16 ypos,u16 radius,u16 color);
void LCD_FillCircle(u16 Xpos, u16 Ypos, u16 Radius, u16 color);
void LCD_DispGrid(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 step,u16 color);
void LCD_DispChar(u16 x,u16 y,u8 ASCII,FONT *tFont,u16 charcolor,u16 backcolor);
void LCD_DispStr(u16 x,u16 y,u8 *str,FONT *tFont,u16 charcolor,u16 backcolor);
void LCD_DispNum(u16 x,u16 y,u32 number,FONT *tFont,u16 numcolor,u16 backcolor);

#endif