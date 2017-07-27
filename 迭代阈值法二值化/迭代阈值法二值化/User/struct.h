#ifndef	__STRUCT_H_
#define __STRUCT_H_

#include "main.h"

/*******************************	typedef	struct variable		******************************/
typedef	struct _tFONT{
		u32 FontName;
		u16 height;
		u16 weight;
}FONT;

//lcd register
typedef struct
{
  vu16 LCD_REG;
  vu16 LCD_RAM;
} LCD_TypeDef;


/*  校正系数结构体 */
typedef struct Parameter 
{						
long double An,  			 //注:sizeof(long double) = 8
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
}Parameter ;

/*			定义坐标参数			*/
typedef	struct Coordinate{
	u16 x;
	u16 y;
}Coordinate;

/*      摄像头地址    */
typedef struct Reg
{
	uint8_t Address;			       /*寄存器地址*/
	uint8_t Value;		           /*寄存器值*/
}Reg_Info;


#endif