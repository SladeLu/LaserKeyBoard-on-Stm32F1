#include "usart.h"
#include "stdio.h"
void Judgement_Test(u32 x,u32 y)		 //x为大头，y为小头
{

	char output = 0;
	//printf("The coordinate is(%d,%d)\r\n",x,y);
	//第一行 （123）4567890
	if(y>=40&&y<=55)
	{
		if(x>=285&&x<=305)	output = '4';
		if(x>=245&&x<=260)	output = '5';
		if(x>=185&&x<=215)	output = '6';
		if(x>=135&&x<=155)	output = '7';
		if(x>=77&&x<=120)	output = '8';
		if(x>=40&&x<=70)	output = '9';
		if(x>0&&x<=30)		output = '0';		
	}
	//第二行 rtyuiop
	if(y>=60&&y<=74)
	{
		if(x>=315&&x<=320)	output = 'w';	
		if(x>=280&&x<=305)	output = 'e';
		if(x>=240&&x<=255)	output = 'r';
		if(x>=185&&x<=215)	output = 't';
		if(x>=135&&x<=155)	output = 'y';
		if(x>=80&&x<=120)	output = 'u';
		if(x>=50&&x<=80)	output = 'i';
		if(x>15&&x<=35)		output = 'o';
		if(x>0&&x<=10)		output = 'p';			
	}
	//第三行 sdfghjkl;
	if(y>=76&&y<=85)
	{
		if(x>=295&&x<=315)	output = 's';	
		if(x>=270&&x<=285)	output = 'd';
		if(x>=220&&x<=245)	output = 'f';
		if(x>=180&&x<=210)	output = 'g';
		if(x>=135&&x<=155)	output = 'h';
		if(x>=90&&x<=120)	output = 'j';
		if(x>=65&&x<=80)	output = 'k';
		if(x>30&&x<=45)		output = 'l';
		if(x>0&&x<=10)		output = ';';		
	}
	//第四行
	if(y>=90&&y<=100)
	{
		if(x>=305&&x<=312)	output = 'z';	
		if(x>=270&&x<=290)	output = 'x';
		if(x>=235&&x<=260)	output = 'c';
		if(x>=190&&x<=220)	output = 'v';
		if(x>=155&&x<=175)	output = 'b';
		if(x>=125&&x<=145)	output = 'n';
		if(x>=85&&x<=110)	output = 'm';
		if(x>60&&x<=80)		output = ',';
		if(x>30&&x<=45)		output = '.';		
	} 
	//SPACE行	
	if(y>=103&&y<=115)
	{
		if(x>=95&&x<=245)	output = ' ';	
		if(x>=75&&x<=85)	output = '\'';
		if(x>=265&&x<=281)	output = ']';
		if(x>=285&&x<=315)	output = '[';
	}
	//printf("Key_%c Pressed",output);
	if(output !=0)		
  	printf("%c",output);		
}
