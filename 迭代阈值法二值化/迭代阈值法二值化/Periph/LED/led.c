#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	/*				��GPIOB�Ķ˿�ʱ��			*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	/*				����ģʽ����			*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//����Ϊ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//����ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure);							//��ʼ������
	
	LED_OFF;		
}

