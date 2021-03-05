#include "SEG_8.h"

code uchar seg7code[ ]={
0x3f,//0
0x06, //1
0x5b, //2
0x4f, //3
0x66, //4
0x6d, //5
0x7d, //6
0x07, //7
0x7f, //8
0x6f, //9
0x73,  //P  10
0x40, //-  11
0x00,   //不显示 12
0x77,  //A  13  
0x7c,  //b	14
0x39,  //c	15
0x5e,//d   16
0xc0,
}; //显示段码 数码管字跟 
/**
*四位数码管显示
**f_flag:小数点
***0：第二位；
***1：第三位；
***2：无小数点；
***3：第四位；
**/    
uchar f_flag1,f_flag2;
uchar w;
void Led(uchar led_a1,uchar led_a2,uchar led_a3,uchar led_a4,uchar led_a5,uchar led_a6,uchar led_a7,uchar led_a8){		
	switch(w){
		case 0:	
			SEG_IO=0;L1=0;L2=1;L3=1;L4=1;L5=1;L6=1;L7=1;L8=1;
			SEG_IO=seg7code[led_a1];w = 1;
		break;
		case 1:
			SEG_IO=0;L1=1;L2=0;L3=1;L4=1;L5=1;L6=1;L7=1;L8=1;w = 2;
				if(f_flag1==0)SEG_IO=seg7code[led_a2]|0x80;	
				else SEG_IO=seg7code[led_a2];
		break;
		case 2:
			SEG_IO=0;L1=1;L2=1;L3=0;L4=1;L5=1;L6=1;L7=1;L8=1;w = 3;
			if(f_flag1==1)SEG_IO=seg7code[led_a3]|0x80;	
			else SEG_IO=seg7code[led_a3];	
		break;
		case 3:
			SEG_IO=0;L1=1;L2=1;L3=1;L4=0;L5=1;L6=1;L7=1;L8=1;w = 4;
			if(f_flag1==3)SEG_IO=seg7code[led_a4]|0x80;	
			else SEG_IO=seg7code[led_a4];
		break;
		case 4:
			SEG_IO=0;L1=1;L2=1;L3=1;L4=1;L5=0;L6=1;L7=1;L8=1;w = 5;
			SEG_IO=seg7code[led_a5];
		break;
		case 5:
			SEG_IO=0;L1=1;L2=1;L3=1;L4=1;L5=1;L6=0;L7=1;L8=1;w = 6;
			if(f_flag2==3)SEG_IO=seg7code[led_a6]|0x80;	
			else SEG_IO=seg7code[led_a6];
		break;
		case 6:
			SEG_IO=0;L1=1;L2=1;L3=1;L4=1;L5=1;L6=1;L7=0;L8=1;w = 7;
			if(f_flag2==3)SEG_IO=seg7code[led_a7]|0x80;	
			else SEG_IO=seg7code[led_a7];
		break;
		case 7:
			SEG_IO=0;L1=1;L2=1;L3=1;L4=1;L5=1;L6=1;L7=1;L8=0;w = 0;
			if(f_flag2==3)SEG_IO=seg7code[led_a8]|0x80;	
			else SEG_IO=seg7code[led_a8];
		break;
	}
}