#include "main.h"

void USART_Config(u32 bound)
{
	GPIO_InitTypeDef	GPIO_InitStrucutre;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/*			enable Colck port				*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	/*			config GPIO pin				*/
	GPIO_InitStrucutre.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;		
	GPIO_InitStrucutre.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStrucutre.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStrucutre.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStrucutre.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrucutre);
	
	/*			config USART1				*/
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	/*		enable USART1			*/
	USART_Cmd(USART1,ENABLE);
	/*			clear transimission complete flag		*/
	USART_ClearFlag(USART1,USART_FLAG_TC);
	
#if	EN_USART1_RX
		/*			open Rx interrupt			*/
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		/*			config NVIC control				*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_Init(&NVIC_InitStructure);
#endif
	
}

#if 1
/*			向C库函数fputc的printf函数重定义		*/
int fputc(int ch, FILE *fp)
{
	USART_SendData(USART1,(uint8_t)ch);
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
	return ch;
}

/*			向C库函数fgetc的scanf函数重定义		*/
int fgetc(FILE *fp)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	
	return (int) USART_ReceiveData(USART1);
}
#endif


void USART1_IRQHandler(void)
{
	u8 ch;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET )
	{
		LED_TOGGLE;
		ch = USART_ReceiveData(USART1);
		USART_SendData(USART1,ch);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);					//clear IT pending flag
	}
}
