#ifndef __KEYINFO_H
#define __KEYINFO_H

#include "sys.h"

u8 Key_Num[10] = {0,0,0,0,0,0,0,0,0,0};
u8 Key[26] = {
			  0,0,0,0,0,0,0,0,0,0,
              0,0,0,0,0,0,0,0,0,0,
			  0,0,0,0,0,0};

u8 Key_Symbol[11]  = {0,0,0,0,0,0,0,0,0,0,0};    

u8 Key_Dir[4] = {0,0,0,0};

u8 Key_SPACE = 0;
u8 Key_TAB = 0;
u8 Key_ESC =0;
u8 Key_CAP =0;
u8 Key_CTL =0;
u8 Key_ALT =0;
u8 Key_SHIFT_L =0;
u8 Key_SHIFT_R =0;
u8 Key_DEL=0;
u8 Key_BACK=0;
u8 Key_ENTER=0;
u8 Key_FN=0;

#define  Key_x         Key_Num[x]

#define  Key_A        Key[0]
#define  Key_B        Key[1]    
#define  Key_C        Key[2]    
#define  Key_D        Key[3]    
#define  Key_E        Key[4]    
#define  Key_F        Key[5]    
#define  Key_G        Key[6]    
#define  Key_H        Key[7]    
#define  Key_I        Key[8]    
#define  Key_J        Key[9]
#define  Key_K        Key[10]
#define  Key_L        Key[11]    
#define  Key_M        Key[12]    
#define  Key_N        Key[13]    
#define  Key_O        Key[14]    
#define  Key_P        Key[15]    
#define  Key_Q        Key[16]    
#define  Key_R        Key[17]    
#define  Key_S        Key[18]    
#define  Key_T        Key[19]     
#define  Key_U        Key[20]    
#define  Key_V        Key[21]    
#define  Key_W        Key[22]    
#define  Key_X        Key[23]    
#define  Key_Y        Key[24]    
#define  Key_Z        Key[25] 

#define  Key_Minus   	Key_Symbol[0]				//-
#define  Key_Add     	Key_Symbol[1]				//+
#define  Key_Semicolon 	Key_Symbol[2]		    	//;
#define  Key_Comma      Key_Symbol[3]				//,
#define  Key_Point      Key_Symbol[4]				//.
#define  Key_Marks      Key_Symbol[5]   			//'
#define  Key_Sprit_L    Key_Symbol[6]  				///
#define  Key_Sprit_R    Key_Symbol[7]  				//'\'
#define  Key_Bracket_L  Key_Symbol[8] 				//[
#define  Key_Bracket_R  Key_Symbol[9] 				//]
#define  Key_Accent 	Key_Symbol[10] 				//`

#define Key_UP		   	Key_Dir[0]
#define Key_DOWN 		Key_Dir[1]
#define Key_LEFT	   	Key_Dir[2]
#define Key_RIGHT	 	Key_Dir[3]

#define x_ON 			x=1
#define x_DOWN  		x=0

#define x_CAPON 		x=-1
#define	x_SHIFTON 		x=-1
#define x_FNON 			x=2  

void Judgement_Test(u32 x,u32 y);
#endif
