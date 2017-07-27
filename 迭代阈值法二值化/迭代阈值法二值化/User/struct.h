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


/*  У��ϵ���ṹ�� */
typedef struct Parameter 
{						
long double An,  			 //ע:sizeof(long double) = 8
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
}Parameter ;

/*			�����������			*/
typedef	struct Coordinate{
	u16 x;
	u16 y;
}Coordinate;

/*      ����ͷ��ַ    */
typedef struct Reg
{
	uint8_t Address;			       /*�Ĵ�����ַ*/
	uint8_t Value;		           /*�Ĵ���ֵ*/
}Reg_Info;


#endif