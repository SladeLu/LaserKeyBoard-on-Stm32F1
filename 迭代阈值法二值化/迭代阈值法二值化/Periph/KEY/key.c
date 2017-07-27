#include "key.h"
#include "delay.h"

/*			������ʼ������				*/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*			�򿪶˿�1 ��ʱ��			*/
	RCC_AHB1PeriphClockCmd(RCC_KEY,ENABLE);

	/*			��ʼ������			*/
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			//����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	  //����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(KEY_PORT,&GPIO_InitStructure);
}

/*
**************************************************
	* ��������Key_Scan
	* ��  ������ⰴ������
	* ��  �룺uint8_t mode�� 0 --- ��֧����������  1 ---  ֧����������
	* ��  ����
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
		if( KEY_VAL==0 )				//��ȡ����ֵ
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
