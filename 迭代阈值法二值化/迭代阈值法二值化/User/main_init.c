#include "main_init.h"


Coordinate display;

/***********************************************************
* function name:	Main_Init
* descripation:		Initial all functions
***********************************************************/
void Main_Init(void)
{
	u8 touch_para_flag;
	
/******************			basic periph on the board			*******************************/	
	LED_Init();												//LED initial
	Delay_Init(168);									//systick initial 
	USART_Config(115200);							//USART1
	printf("串口初始化成功\n");
	LCDILI9325_Init();								//ILI9325 initial
	LCD_Fill(0,0,320,240,BLACK);			//clear screen
	
	SPI_FLASH_Init();									//flash initial
	SPI1_Init();											//touch spi1 initial
	Touch_Init();											//touch initial
  KEY_Init();
	SPI_FLASH_WriteASCII();
	
	/*				校验触摸屏校准参数				*/
	SPI_FLASH_BufferRead(&touch_para_flag,TOUCH_PARA_FLASHADDRESS,1);
	if( touch_para_flag!=0xCC )
		while(Touch_Calibrate(0xCC)!=0);
/*************************************************************************************/

	LCD_Fill(0,150,320,5,RED);
	LCD_DispStr(30,190,"the itera_threshold process image",&Font8x16,CYAN,BLACK);
	LCD_DispStr(80,220,"OV7725 Camera picture",&Font8x16,CYAN,BLACK);
	
	ov7725_InitConfig();					//ov7725总的初始化函数
	
}