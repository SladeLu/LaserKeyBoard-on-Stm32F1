#ifndef	__LCD_H_
#define __LCD_H_

#include "main.h"
#include "struct.h"

/*
* 说  明：DISP_MODE --- 选择显示方向
					1  --- 左上->右下 竖屏
					2  --- 左下->右上 横屏
					3  --- 右下->左上 竖屏
					4  --- 右上->左上 横屏
*/
#define DISP_MODE 2

/*			设置屏幕大小			*/
#define WEIGH			320
#define HIGH			240

//颜色
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
#define BROWN 			 		 0XBC40 //棕色
#define BRRED 			 		 0XFC07 //棕红色
#define GRAY  			 		 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色

#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
#define LCD         ((LCD_TypeDef *) LCD_BASE)

#define LCD_WriteIndex(index) 				LCD->LCD_REG=index
#define LCD_WriteData(data)						LCD->LCD_RAM=data


//函数声明
void LCDILI9325_Init();
void LCD_SetCursor(u16 x,u16 y);
void LCD_SetWindows(u16 startx,u16 starty,u16 endx,u16 endy);
void LCD_Clear(u16 color);
u16 LCD_GetPoint(u16 x,u16 y);
void LCD_SetPoint(u16 x,u16 y,u16 point);

/**********************					应用函数					********************************/
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