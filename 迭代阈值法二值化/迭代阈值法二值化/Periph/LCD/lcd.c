#include "lcd.h"

//#define Bank_LCD_C								((u32)0x6C000000)		//Disp REG ADDR
//#define Bank_LCD_D								((u32)0x6D000000)		//Disp DATA ADDR

////��  �� :  дili9325�������Ĵ�����ַ
//#define LCD_WriteIndex(index)			*(vu16 *)(Bank_LCD_C)=index
////��  �� �� д����
//#define LCD_WriteData(data)				*(vu16 *)(Bank_LCD_D)=data
////��  �� �� ������
//#define LCD_ReadData()						*(vu16 *)(Bank_LCD_D)

////��ָ���Ĵ����ж�ȡ�Ĵ�����ֵ���ڲ�����
//u16 LCD_ReadRegister(u16 index)
//{
//	LCD_WriteIndex(index);
//	return LCD_ReadData();
//}

///****************************************************************
//* ��������LCD_WriteRegister
//* ��  �ܣ���ָ���Ĵ�����ַдֵ
//* ��  �룺u16 index���Ĵ�����ַ    
//					u16 data ��Ҫд��Ĵ�����ֵ
//* ˵  �����ڲ�����
//*****************************************************************/
//void LCD_WriteRegister(u16 index,u16 data)
//{
//	LCD_WriteIndex(index);
//	LCD_WriteData(data);
//}






u16 LCD_ReadData(void)
{
	LCD->LCD_REG=0x22;
	return LCD->LCD_RAM;
}

void LCD_WriteRegister(u16 index,u16 data)
{
	LCD->LCD_REG = index;
	LCD->LCD_RAM = data;
}

u16 LCD_ReadRegister(u16 index)
{
	LCD->LCD_REG = index;
	return (LCD->LCD_RAM);
}


/****************************************************************
* ��������LCD_Reset
* ��  �ܣ�LCD��λ����
* ��  �룺��
* ˵  �����ڲ�����
*****************************************************************/
void LCD_Reset(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0);					//PF0   LCD_RST  PF0=0
	delay_ms(200);
	GPIO_SetBits(GPIOF,GPIO_Pin_0);						//PF0   LCD_RST  PF0=0
	delay_ms(200);
}

/*****************************************************************
* ��������LCD_GPIOInit
* ��  �ܣ�ILI9325Һ�����ܽų�ʼ��
******************************************************************/
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE| RCC_AHB1Periph_GPIOG| RCC_AHB1Periph_GPIOF , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
								 GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
							 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//(RS)
	GPIO_Init(GPIOF, &GPIO_InitStructure);  
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FSMC);	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//(CS) 
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_FSMC);
}

/*****************************************************************
* ��������LCD_FSMCInit
* ��  �ܣ�����ILI9325Һ������FSMC��ʼ��
******************************************************************/
void LCD_FSMCInit(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	p.FSMC_AddressSetupTime = 0;
	p.FSMC_AddressHoldTime = 0;
	p.FSMC_DataSetupTime = 7;
	p.FSMC_BusTurnAroundDuration = 0;
	p.FSMC_CLKDivision = 0;
	p.FSMC_DataLatency = 0;
	p.FSMC_AccessMode = FSMC_AccessMode_A;


	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

/****************************************************************
* ��������LCDILI9325_Init
* ��  �ܣ���ʼ��LCDili9325Һ����
* ��  �룺��
* ��  ������
****************************************************************/
void LCDILI9325_Init()
{
	LCD_GPIOInit();					//GPIO��ʼ��
	LCD_FSMCInit();					//FSMC��ʼ��
	LCD_Reset();						//LCD ��λ
	
	LCD_WriteRegister(0x00E3,0x3008);
	LCD_WriteRegister(0x00E7,0x0012);
	LCD_WriteRegister(0x00EF,0x1231);
	LCD_WriteRegister(0x0000,0x0001);					//������Դ�ڲ�ʱ��
	LCD_WriteRegister(0x0001,0x0100);     
	LCD_WriteRegister(0x0002,0x0700);					//��Դ����
	
	/*	//LCD_WriteRegister(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(�Ĵ��� 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D   ���������
		// 1  1   1	   U->D	L->R			*/
		
		//SR ��������Ͻ�
		//BGR   ��ɫλ   0 --- BGR ��ɫ   1 --- RGB ��ɫ
		//AM ˮƽ��ֱλ  0 --- ˮƽ       1 --- ��ֱ (�����������)
		//BIT3=AM BIT4:5=ID0:1
		// ID1 ID0  AM  FUNCATION
		
		//  0   0    1  �� -> ��    �� -> ��   
		//  0   1    1	�� -> ��    �� -> �� //��������ͷ�������ģʽ
		//  1   0    1  �� -> ��    �� -> ��
		//  1   1    1  �� -> ��    �� -> ��  
		//  
		
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D   ���������
		// 1  1   1	   U->D	L->R			*/
		
		
		
		

	LCD_WriteRegister(0x0003,(1<<12)|(1<<4)|(1<<3) );//65K    
	LCD_WriteRegister(0x0004,0x0000);                                   
	LCD_WriteRegister(0x0008,0x0207);	           
	LCD_WriteRegister(0x0009,0x0000);         
	LCD_WriteRegister(0x000a,0x0000);//display setting  1 frame       
	LCD_WriteRegister(0x000c,0x0001);//display setting  16 bit      
	LCD_WriteRegister(0x000d,0x0000);//0f3c          
	LCD_WriteRegister(0x000f,0x0000);
	
	//��Դ����
	LCD_WriteRegister(0x0010,0x0000);   
	LCD_WriteRegister(0x0011,0x0007);
	LCD_WriteRegister(0x0012,0x0000);                                                                 
	LCD_WriteRegister(0x0013,0x0000);                 
	delay_ms(1); 
	LCD_WriteRegister(0x0010,0x1590);   
	LCD_WriteRegister(0x0011,0x0227);
	delay_ms(1); 
	LCD_WriteRegister(0x0012,0x009c);                  
	delay_ms(1); 
	LCD_WriteRegister(0x0013,0x1900);   
	LCD_WriteRegister(0x0029,0x0023);
	LCD_WriteRegister(0x002b,0x000e);
	delay_ms(1); 
	LCD_WriteRegister(0x0020,0x0000);                                                            
	LCD_WriteRegister(0x0021,0x013f);           
	delay_ms(1); 
	
	//٤��У��
	LCD_WriteRegister(0x0030,0x0007); 
	LCD_WriteRegister(0x0031,0x0707);   
	LCD_WriteRegister(0x0032,0x0006);
	LCD_WriteRegister(0x0035,0x0704);
	LCD_WriteRegister(0x0036,0x1f04); 
	LCD_WriteRegister(0x0037,0x0004);
	LCD_WriteRegister(0x0038,0x0000);        
	LCD_WriteRegister(0x0039,0x0706);     
	LCD_WriteRegister(0x003c,0x0701);
	LCD_WriteRegister(0x003d,0x000f);
	delay_ms(1); 
	LCD_WriteRegister(0x0050,0x0000); //ˮƽGRAM��ʼλ��
	LCD_WriteRegister(0x0051,0x00ef); //ˮƽGRAM��ֹλ��                  
	LCD_WriteRegister(0x0052,0x0000); //��ֱGRAM��ʼλ��
	LCD_WriteRegister(0x0053,0x013f); //��ֱGRAM��ֹλ��    
	
	LCD_WriteRegister(0x0060,0xa700);        
	LCD_WriteRegister(0x0061,0x0001); 
	LCD_WriteRegister(0x006a,0x0000);
	LCD_WriteRegister(0x0080,0x0000);
	LCD_WriteRegister(0x0081,0x0000);
	LCD_WriteRegister(0x0082,0x0000);
	LCD_WriteRegister(0x0083,0x0000);
	LCD_WriteRegister(0x0084,0x0000);
	LCD_WriteRegister(0x0085,0x0000);

	LCD_WriteRegister(0x0090,0x0010);     
	LCD_WriteRegister(0x0092,0x0000);  
	LCD_WriteRegister(0x0093,0x0003);
	LCD_WriteRegister(0x0095,0x0110);
	LCD_WriteRegister(0x0097,0x0000);        
	LCD_WriteRegister(0x0098,0x0000);  
	
	//������ʾ����
	LCD_WriteRegister(0x0007,0x0133);   
	LCD_WriteRegister(0x0020,0x0000);                                                            
	LCD_WriteRegister(0x0021,0x013f); 
}

/*************************************************************
* ��  �ܣ�������Ļ������
* ��  �룺u16 x��������
					u16 y��������
* ˵  ����DISP_MODE --- ѡ����ʾ����
					1  --- ����->���� ����
					2  --- ����->���� ����
					3  --- ����->���� ����
					4  --- ����->���� ����
**************************************************************/
void LCD_SetCursor(u16 x,u16 y)
{
	switch(DISP_MODE)	
	{	
		case 1:
				LCD_WriteRegister(0x20,x);
				LCD_WriteRegister(0x21,y);
		break;
		case 2:
				LCD_WriteRegister(0x20,y);
				LCD_WriteRegister(0x21,319-x);
		break;
		case 3:
				LCD_WriteRegister(0x20,240-x);
				LCD_WriteRegister(0x21,319-y);
		break;
		case 4:
				LCD_WriteRegister(0x20,240-y);
				LCD_WriteRegister(0x21,x);
		break;
	}
}

/*************************************************************
* ��������LCD_SetWindows
* ��  �ܣ����ô�������
* ��  �룺u16 startx��  ����ʼ����
					u16 starty��  ����ʼ����
					u16 endx ��   �е���ֹ����
					u16 endy ;    �е���ֹ����
* ���Ʒ����� LCD_SetWindows(0,0,100,100)
**************************************************************/
void LCD_SetWindows(u16 startx,u16 starty,u16 endx,u16 endy)
{
	LCD_SetCursor(startx,starty);
	LCD_WriteRegister(0x50,startx);
	LCD_WriteRegister(0x51,starty);
	LCD_WriteRegister(0x52,endx);
	LCD_WriteRegister(0x53,endy);
}

/***********************************************************
* ��������LCD_Clear
* ��  �ܣ���LCD����
* ��  �룺u16 color����������ɫ
* ���÷�����LCD_Clear(BLACK);
************************************************************/
void LCD_Clear(u16 color)
{
	u32 i;
	LCD_SetCursor(0x00,0x00);
	LCD_WriteIndex(0x22);
	for( i=0;i<76800;i++ )
		LCD_WriteData(color);
}

/***********************************************************
* ��������LCD_GetPoint
* ��  �ܣ���ȡLCD����һ���������ɫֵ
* ��  �룺u16 x��  ��ĺ�����
					u16 y��  ���������
* ���÷�����color = LCD_GetPoinr(100,100);
************************************************************/
u16 LCD_GetPoint(u16 x,u16 y)
{
	u16 temp;
	LCD_SetCursor(x,y);
	LCD_WriteIndex(0x22);
	temp = LCD_ReadData();	
	return temp;
}

/***********************************************************
* ��������LCD_SetPoint
* ��  �ܣ���ָ���ط�����
* ��  �룺u16 x��  ��ĺ�����
					u16 y��  ���������
					u16 point�� �����ɫ
* ���÷�����LCD_SetPoint(100,100,BLACK);
************************************************************/
void LCD_SetPoint(u16 x,u16 y,u16 point)
{
	if( DISP_MODE == 1 || DISP_MODE == 3 )			//����
		if(x>240 || y>320)	return;		
	if( DISP_MODE == 2 || DISP_MODE == 4 )			//����
		if(x>320 || y>240)	return;
		
	LCD_SetCursor(x,y);
	LCD_WriteIndex(0x22);					//׼��д������
	LCD_WriteData(point);
}

/************************************************************
* ��������LCD_DrawPicture
* ��  �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ��  �룺startx��   �е���ʼ����
					starty��   �е���ʼ����
					endx��		 �е���ֹ����
					endy��     �е���ֹ����
* ˵  ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
* ���÷�����LCD_DrawPicture(0,0,100,100,(u16*)demo);
*************************************************************/
void LCD_DrawPicture(u16 startx,u16 starty,u16 endx,u16 endy,u16 *pic)
{
	u16 i;
	LCD_SetWindows(startx,starty,endx,endy);
	LCD_SetCursor(startx,starty);
	LCD_WriteIndex(0x22);
	for(i=0;i<(endx*endy);i++)
		LCD_WriteData(*pic++);
}

/************************************************************
* ��������LCD_DispChar
* ��  �ܣ���ָ��λ����ʾһ��ASCII�ַ�
* ��  �룺u16 x:	�е���ʼ����
					u16 y:  �е���ʼ����
					u8 ASCII��ASCII�ַ�
					FONT �� ѡ��Ҫд������
					u16 charcolor���������ɫ
					u16 backcolor��ѡ��������ɫ
* ˵  ����FONT�������ѡ�� 8x16 ...�ü������� 
					��������8x16������ȡģ��ʽ��һ����������һ�ֻ��㷽ʽ
* ���÷�����LCD_DispChar(100,100,'A',Font8x16,WHITE,BLACK);
*************************************************************/
void LCD_DispChar(u16 x,u16 y,u8 ASCII,FONT *tFont,u16 charcolor,u16 backcolor)
{
	u16 page=0,column=0;
	u16 tmp_char=0,temp;
	u16 array[24];
		
	/*			���ⲿFLASH�����ȡASCII�ַ�		*/
	if( tFont->FontName==1624 )
		SPI_FLASH_BufferRead((void *)array,ASCII16x24_FLASHADDRESS+(ASCII-0x20)*2*tFont->height,tFont->height*2);
	else if( tFont->FontName==816 )
		SPI_FLASH_BufferRead((void *)array,ASCII8x16_FLASHADDRESS+(ASCII-0x20)*2*tFont->height,tFont->height*2);
	else if( tFont->FontName==612 )
		SPI_FLASH_BufferRead((void *)array,ASCII6x12_FLASHADDRESS+(ASCII-0x20)*2*tFont->height,tFont->height*2);
	
	if( tFont->FontName==1624 || tFont->FontName==612 )
	{
		/*			���ַ�		*/
		for( page=0;page<tFont->height;page++ )
		{
			tmp_char = array[page];		//�ҵ��ֿ��������ASCII��ͷλ��
			for( column=0;column<tFont->weight;column++ )
			{
				if( (tmp_char&0x01) == 0x01)
					LCD_SetPoint(x+column,y+page,charcolor);
				else
					LCD_SetPoint(x+column,y+page,backcolor);
				tmp_char>>=1;
			}		/*			һ���Ѿ�д��				*/
		}			/*			һ�����Ѿ�д��			*/
	}
	else if( tFont->FontName==816 )
	{
		/*			���ַ�		*/
		for( page=0;page<tFont->height;page++ )
		{
			tmp_char = array[page];		//�ҵ��ֿ��������ASCII��ͷλ��
			for( column=0;column<tFont->weight;column++ )
			{
				temp = tmp_char;
				if( ((temp>>(tFont->weight-1-column))&0x01) == 0x01)
					LCD_SetPoint(x+column,y+page,charcolor);
				else
					LCD_SetPoint(x+column,y+page,backcolor);;
			}		/*			һ���Ѿ�д��				*/
		}			/*			һ�����Ѿ�д��			*/
	}

		

}

/*			��ʾ�ַ���			*/
void LCD_DispStr(u16 x,u16 y,u8 *str,FONT *tFont,u16 charcolor,u16 backcolor)
{
	while( *str != '\0' )
	{
		if( x+tFont->weight > WEIGH )
		{
			x=0;
			y += tFont->height;
		}
		if( y+tFont->height > HIGH )
		{
			y=0;
		}
		LCD_DispChar(x,y,*str,tFont,charcolor,backcolor);
		x += tFont->weight;
		str++;
	}
}

/**************************************************************************
* ��������LCD_Fill
* ��  �ܣ�����Ļ���滭һ����������
* ��  �룺u16 startx:     ���������е���ʼλ��
					u16 starty:			���������е���ʼλ��
					u16 xsize��			��������ĳ�
					u16 ysize��			��������Ŀ�
					u16 color��     ������ɫ
* ���÷�����LCD_Fill(100,100,20,20,RED);
**************************************************************************/
void LCD_Fill(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 color)
{
	u16 page,column;
	LCD_SetCursor(startx,starty);
	for( page=0;page<ysize;page++ )
	{
		for( column=0;column<xsize;column++ )
			LCD_SetPoint(startx+column,starty+page,color);
	}
}

/**************************************************************************
* ��������LCD_Rect
* ��  �ܣ���һ���ߵľ���
* ��  �룺u16 startx:     �����е���ʼλ��
					u16 starty:			�����е���ʼλ��
					u16 xsize��			��������ĳ�
					u16 ysize��			��������Ŀ�
					u16 color��     ���ε���ɫ
* ���÷�����LCD_Rect(10,10,50,50,RED);
**************************************************************************/
void LCD_Rect(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 color)
{
	LCD_Fill(startx,starty,xsize,1,color);
	LCD_Fill(startx,starty+ysize-1,xsize,1,color);
	LCD_Fill(startx,starty,1,ysize,color);
	LCD_Fill(startx+xsize-1,starty,1,ysize,color);
}

/**************************************************************************
* ��������LCD_DispGrid
* ��  �ܣ���ָ��λ�û�һ���ƶ���С��ָ��������դ��
* ��  �룺u16 startx:     դ���е���ʼλ��
					u16 starty:			դ���е���ʼλ��
					u16 xsize��			դ���еĳ���
					u16 ysize��			դ���еĳ���
					u16 step��			դ���Ĳ���
					u16 color:			դ�����ɫ
* ���÷�����LCD_DispGrid(100,100,50,50,10,RED);
**************************************************************************/
void LCD_DispGrid(u16 startx,u16 starty,u16 xsize,u16 ysize,u16 step,u16 color)
{
	u16 i;
	for( i=0;i<=xsize;i+=step )
		LCD_Fill(startx+i,starty,1,ysize,color);
	for( i=0;i<=ysize;i+=step )
		LCD_Fill(startx,starty+i,xsize,1,color);
}

/**************************************************************************
* ��������LCD_Circle
* ��  �ܣ�����Ļ���滭һ��Բ
* ��  �룺u16 xpos:     Բ���е������
					u16 ypos:			Բ���е�������
					u16 Radius    Բ�İ뾶
					u16 color��   ��Բ����ɫ
* ���÷�����LCD_Circle(100,100,10,RED);
**************************************************************************/
void LCD_Circle(u16 Xpos, u16 Ypos, u16 Radius, u16 color)
{
	s32  Dec;
	u32  CurX;
	u32  CurY;
 

	CurX=0;
	CurY=Radius;   
	Dec=3-(Radius<<1);
	while(CurX<=CurY)
	{
		
		LCD_SetPoint(Xpos+CurX,Ypos+CurY,color);
		LCD_SetPoint(Xpos+CurX,Ypos-CurY,color);
		LCD_SetPoint(Xpos-CurX,Ypos+CurY,color);
		LCD_SetPoint(Xpos-CurX,Ypos-CurY,color);
		LCD_SetPoint(Xpos+CurY,Ypos+CurX,color);
		LCD_SetPoint(Xpos+CurY,Ypos-CurX,color);
		LCD_SetPoint(Xpos-CurY,Ypos+CurX,color);
		LCD_SetPoint(Xpos-CurY,Ypos-CurX,color);
		
		
		if(Dec<0)Dec+=(CurX<<2)+6;
		else
		{
				Dec+=((CurX-CurY)<<2)+10;
				CurY--;
		}
		CurX++;
	}
}

/**************************************************************************
* ��������LCD_FillCircle
* ��  �ܣ�����Ļ���滭һ���м����Բ
* ��  �룺u16 xpos:     Բ���е������
					u16 ypos:			Բ���е�������
					u16 Radius    Բ�İ뾶
					u16 color��   ��Բ����ɫ
* ���÷�����LCD_Circle(100,100,10,RED);
**************************************************************************/
void LCD_FillCircle(u16 Xpos, u16 Ypos, u16 Radius, u16 color)
{
	s32  Dec;
	u32  i;
	u32  CurX;
	u32  CurY;
 

	CurX=0;
	CurY=Radius;   
	Dec=3-(Radius<<1);
	while(CurX<=CurY)
	{
		
		for( i=0;i<=CurY;i++ )
			LCD_SetPoint(Xpos+CurX,Ypos+i,color);
		for( i=0;i<=CurY;i++ )
			LCD_SetPoint(Xpos-CurX,Ypos+i,color);
		for( i=0;i<=CurX;i++ )
			LCD_SetPoint(Xpos+CurY,Ypos+i,color);
		for( i=0;i<=CurX;i++ )
			LCD_SetPoint(Xpos-CurY,Ypos+i,color);
		for( i=0;i<=CurY;i++ )
			LCD_SetPoint(Xpos+CurX,Ypos-i,color);
		for( i=0;i<=CurY;i++ )
			LCD_SetPoint(Xpos-CurX,Ypos-i,color);
		for( i=0;i<=CurX;i++ )
			LCD_SetPoint(Xpos+CurY,Ypos-i,color);
		for( i=0;i<=CurX;i++ )
			LCD_SetPoint(Xpos-CurY,Ypos-i,color);
		
		
		if(Dec<0)Dec+=(CurX<<2)+6;
		else
		{
				Dec+=((CurX-CurY)<<2)+10;
				CurY--;
		}
		CurX++;
	}
}

/************************************************************
* ��������LCD_DispNum
* ��  �ܣ���ָ����λ����ʾ��Ҫ��ʾ��һ������
* ��  �룺u16 x:	�е���ʼ����
					u16 y:  �е���ʼ����
					u32 number��Ҫ��ʾ������
					FONT �� ѡ��Ҫд������
					u16 charcolor���������ɫ
					u16 backcolor��ѡ��������ɫ
* ˵  ����FONT�������ѡ�� 8x16 ...�ü������� 
					��������8x16������ȡģ��ʽ��һ����������һ�ֻ��㷽ʽ
* ���÷�����LCD_DispChar(100,100,1213,&Font8x16,WHITE,BLACK);
*************************************************************/
void LCD_DispNum(u16 x,u16 y,u32 number,FONT *tFont,u16 numcolor,u16 backcolor)
{
	u8 count=0;							//λ��
	u32 num;
	u8 cap_arr[15];
	num = number;
	/*			��������ĸ���λ�����浽������ȥ			*/
	while(num>0)
	{
		cap_arr[count++]=num%10;
		num = num/10;
	}
	num=count-1;				//�õ�λ��
	
	if( count>0 )
	{
		while( (count--) >0 )
			LCD_DispChar(x+count*tFont->weight,y,0x30+cap_arr[num-count],tFont,numcolor,backcolor);
	}
	else
		LCD_DispChar(x,y,0x30+number,tFont,numcolor,backcolor);
}




