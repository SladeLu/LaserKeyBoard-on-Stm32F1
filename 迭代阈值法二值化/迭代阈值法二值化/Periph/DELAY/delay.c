#include "delay.h"

static uint8_t  fac_us=0;//us��ʱ������			   
static uint16_t fac_ms=0;//ms��ʱ������

/*			SysTick��ʼ������   SYSCLK  --  �ڲ�ʱ��Ƶ��			*/
void Delay_Init(uint8_t SYSCLK)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//ϵͳʱ��8��Ƶ����Ϊ��ʱ��ʱ��
	fac_us=SYSCLK/8;	
	fac_ms=fac_us*1000;
}

/*				��ʱ΢�뺯��				*/
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD = nus*fac_us;			//ʱ�����
	SysTick->VAL = 0x00;						//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//�򿪵δ�ʱ��
	do
	{
		temp = SysTick->CTRL;					//��ȡSysTick��״ֵ̬
	}while((temp&0x01) && !(temp&(1<<16)));			//�ȴ�ʱ�䵽��  0x01 ʹ�ܵδ�ʱ��  1<<16  ������ɱ�־λ
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رյδ�ʱ��
	SysTick->VAL = 0x00;						//��ռ�����
}

/*				��ʱ�̺��뺯��	 (�ڲ�����)	  */
void delay_xms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD = (uint32_t)nms*fac_ms;		//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;				
}

/*			��ʱ���뺯��			*/
void delay_ms(uint16_t nms)
{
	uint8_t repeat=nms/540;	//���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
													//���������ټ�һ��ѭ��
	uint16_t remain=nms%540;
	/*			ѭ��			*/
	while(repeat--)
		delay_xms(540);
	delay_xms(remain);
}