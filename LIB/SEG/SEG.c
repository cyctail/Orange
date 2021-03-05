#include "SEG.h"

code uchar seg7code[ ]={//显示段码 数码管字跟 
0x3f,	//0
0x06,	//1
0x5b,	//2
0x4f,	//3
0x66,	//4
0x6d,	//5
0x7d,	//6
0x07,	//7
0x7f,	//8
0x6f,	//9
0x77,	//A	10  
0x7c,	//b	11
0x39,	//c	12
0x5e,	//d	13
0x73,	//P	14
0x40,	//_NET	15
0x00,	//_TAP  16
0xc0,
};
/**
*四位数码管显示
**f_flag:小数点
***0：第二位；
***1：第三位；
***2：无小数点；
***3：第四位；
**/    

/**/
uchar xdata f_flag;		//小数点控制
uchar xdata seg_w=0;	//位选控制
void Led(uchar a,uchar b,uchar c,uchar d,uchar seg_flag){	
	uchar ZC_sdata,Dis_Dot;
	L1=1;L2=1;L3=1;L4=1;
	switch(seg_w){
		case 0: L1=0; seg_w++; ZC_sdata=a; Dis_Dot=255; break;
		case 1: L2=0; seg_w++; ZC_sdata=b; Dis_Dot=0; 	break;
		case 2: L3=0; seg_w++; ZC_sdata=c; Dis_Dot=1; 	break;
		case 3: L4=0; seg_w=0; ZC_sdata=d; Dis_Dot=3; 	break;
	}
	if(seg_flag==Dis_Dot)SEG_IO=seg7code[ZC_sdata]|0x80;else SEG_IO=seg7code[ZC_sdata];
}



/**/ 
uchar xdata S_Flash=0;
uchar xdata w1,w2,w3,w4;
void SEG_Flash(uchar a,uchar b,uchar c,uchar d,bit flash1,bit flash2,bit flash3,bit flash4){
	if(++S_Flash>=100)S_Flash=0;
	if(flash1)w1=a;else{if(S_Flash<50)w1=a;else w1=_TAP;}
	if(flash2)w2=b;else{if(S_Flash<50)w2=b;else w2=_TAP;}
	if(flash3)w3=c;else{if(S_Flash<50)w3=c;else w3=_TAP;}
	if(flash4)w4=d;else{if(S_Flash<50)w4=d;else w4=_TAP;}
}
/**/
void SEG_F_T1(uchar seg_head,uint seg_data,uchar fnum){
	uchar fa1,fa2,fa3,fa4;
	bit fl1,fl2,fl3,fl4;
	fa1=seg_data%10000/1000;
	fa2=seg_data%1000/100;
	fa3=seg_data%100/10;
	fa4=seg_data%10;
	switch(fnum){
		case 0: fl1=0;fl2=0;fl3=0;fl4=0; break;
		case 1: fa1=seg_head;fl1=1;fl2=0;fl3=0;fl4=0; break;
		case 2: fa2=seg_head;fl1=0;fl2=1;fl3=0;fl4=0; break;
		case 3: fa3=seg_head;fl1=0;fl2=0;fl3=1;fl4=0; break;
		case 4: fa4=seg_head;fl1=0;fl2=0;fl3=0;fl4=1; break;
	}
	SEG_Flash(fa1,fa2,fa3,fa4,fl1,fl2,fl3,fl4);
}
