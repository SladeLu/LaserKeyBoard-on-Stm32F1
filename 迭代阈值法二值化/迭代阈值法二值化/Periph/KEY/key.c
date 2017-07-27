#include "key.h"
#include "delay.h"

/*			按键初始化函数				*/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*			打开端口1 的时钟			*/
	RCC_AHB1PeriphClockCmd(RCC_KEY,ENABLE);

	/*			初始化引脚			*/
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			//输入模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  //上拉模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(KEY_PORT,&GPIO_InitStructure);
}

/*
**************************************************
	* 函数名：Key_Scan
	* 描  述：检测按键函数
	* 输  入：uint8_t mode： 0 --- 不支持连续按键  1 ---  支持连续按键
	* 输  出：
**************************************************
*/
char Key_Scan(uint8_t mode)
{
	if(mode)								
	{
		if( KEY_VAL==0 )
		{
			delay_ms(500);
			if( KEY_VAL==0 )
				return -1;
		}
	}
	else
	{
		if( KEY_VAL==0 )				//读取按键值
		{
			delay_ms(10);
			if( KEY_VAL==0 )
			{
				while(KEY_VAL==0);
				return 1;
			}
		}
		return 0;
	}
}
