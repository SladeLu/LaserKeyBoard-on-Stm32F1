#include "main.h"

int main()
{
	u16 i=0,j=0;
	Main_Init();
	
	while(1)
	{
		

		
		//�õ�����������ĵ�
//		if( Get_touch_point(&display,Read_2046_2())!=DISABLE )
//		{
//			LED_TOGGLE;
//		}
	  ov7725_capanddisp();

	  LED_TOGGLE;
		
		if( Key_Scan(0) == 1 ){
			
		//������ֵ�ָ�ͼ��
		Itera_Threshold();
		  while(1);
		}
		
	}
}