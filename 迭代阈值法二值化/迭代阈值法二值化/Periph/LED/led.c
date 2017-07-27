#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	/*				打开GPIOB的端口时钟			*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	/*				引脚模式配置			*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//设置为输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推完输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//输出速度
	GPIO_Init(GPIOB,&GPIO_InitStructure);							//初始化引脚
	
	LED_OFF;		
}

