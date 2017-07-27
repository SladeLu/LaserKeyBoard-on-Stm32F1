#include "delay.h"

static uint8_t  fac_us=0;//us延时倍乘数			   
static uint16_t fac_ms=0;//ms延时倍乘数

/*			SysTick初始化函数   SYSCLK  --  内部时钟频率			*/
void Delay_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//系统时钟8分频来作为定时器时钟
	fac_us=SYSCLK/8;	
	fac_ms=fac_us*1000;
}

/*				延时微秒函数				*/
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD = nus*fac_us;			//时间加载
	SysTick->VAL = 0x00;						//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//打开滴答定时器
	do
	{
		temp = SysTick->CTRL;					//读取SysTick的状态值
	}while((temp&0x01) && !(temp&(1<<16)));			//等待时间到达  0x01 使能滴答定时器  1<<16  计数完成标志位
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭滴答定时器
	SysTick->VAL = 0x00;						//清空计数器
}

/*				延时短毫秒函数	 (内部调用)	  */
void delay_xms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD = (uint32_t)nms*fac_ms;		//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;				
}

/*			延时毫秒函数			*/
void delay_ms(uint16_t nms)
{
	uint8_t repeat=nms/540;	//比如超频到248M的时候,delay_xms最大只能延时541ms左右了
													//所以这里再加一个循环
	uint16_t remain=nms%540;
	/*			循环			*/
	while(repeat--)
		delay_xms(540);
	delay_xms(remain);
}