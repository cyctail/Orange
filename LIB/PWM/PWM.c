/*2018.5.18
频率 ：1HZ～150KHZ可调。占空比：0到100% 百分之一可调
STC8F2K08S2-SSOP20
启用STC8A8K系列中的高精度PWM模块+TIMER2作为分频器，未使用中断

2018.5.25
改用STC8A8K64S4A12-LQFP48
启用STC8A8K系列中的15bit增强型PWM模块+TIMER2作为分频器，未使用中断
*/

#include "PWM.h"
#include "INTRINS.H"

unsigned char dute=50;
unsigned long freq=1*1000;

#define EE P_SW2|=0x80  //使能访问XSFR
#define ED P_SW2&=~0x80 //禁能访问XSFR

void PWM_init(void){  	//定时器2固定为16位自动重载
	AUXR&=~8;//定时器
	AUXR|=4;//1T模式
	T2L=65536-1000;T2H=(65536-1000)>>8;

	PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
	P2M0=P2M1=0;//设置为输出脚

	EE;  
	PWMCKS = 0x10;                  //选择PWM的时钟为T2溢出率（该寄存器分频无效）
	PWMC = 1000;                    //设置PWM周期
	PWM0T1=0x0000;                  //设置PWM2第1次反转的PWM计数
	PWM0T2=SYS_FREQ/27000 * 50 / 100;      //设置PWM2第2次反转的PWM计数
										//占空比为(PWM0T2-PWM0T1)/PWMC
	PWM0CR =0x80; //输出使能，初始低电平,禁用中断
	ED;            
	PWMCR = 0xc0;  
	AUXR|=0x10;                     //启动定时器2
	PWMCR = 0x00;
}

/*=====================================================
Description:
function:
input   :
output  :
return  :
note    :
=====================================================*/
// unsigned  long PWM_set(unsigned long fr,unsigned int du)
// {
// 	unsigned long div;
// 	if(du==0 || du>=100 || fr==0){   
// 		EE;PWM0CR =0x00;ED;
// 		if(du==0 || fr==0) {P20=0;}
// 		else {P20=1;du=100;}
// 	}else{
// 		div=SYS_FREQ/fr;
// 		if(div<65536/2*10){
// 			div=div;
// 			EE;PWMCKS = 0x00; ED;
// 		}else{
// 			div=(fr<1000)?10000:1000;
// 			T2L=65536-div;T2H=(65536-div)>>8;
// 			EE; PWMCKS = 0x10; ED;
// 			div=(SYS_FREQ/div)/fr;
// 		}
// 		EE;
// 		PWMC=div*10;   
// 		PWM0T2=div*(100-du)/10;
// 		PWM0CR =0x80;
// 		ED;
// 	}  
// 	return 1;
// }
/*=====================================================*/
/*
#define Fosc 	27000000
#define USFr 	1000
#define T0_TIM	(65536-(Fosc/USFr))
*/
#define PWM_MUX 1
#define Fosc 	27000000
// unsigned  long PWM_set(unsigned long fr,unsigned int du)
// {
// 	unsigned long div;
// 	if(du==0 || du>=100 || fr==0){   
// 		EE;PWM0CR =0x00;ED;
// 		if(du==0 || fr==0) {P20=0;}
// 		else {P20=1;du=100;}
// 	}else{								//27 000 000 / fr
// 		div=SYS_FREQ/fr;
// 		// if(div<65536/2){			  	//32768
// 			// EE;PWMCKS = 0x00; ED;
// 		// }else{
// 			// div=(fr<100)?10000:1000;		//
// 			T2L=(65536-(Fosc*fr));T2H=(65536-(Fosc*fr))>>8;
// 			EE; PWMCKS = 0x10; ED;
// 			div=65536-100;
// 		// }
// 		EE;
// 		PWMC=div;
// 		PWM0T2=div*(100-du)/100;
// 		PWM0CR =0x80;
// 		ED;
// 	}  
// 	return 1;
// }

unsigned  long PWM_set(unsigned long fr,unsigned int du)
{
	unsigned long div;
	if(du==0 || du>=100 || fr==0){   
		EE;PWM0CR =0x00;ED;
		if(du==0 || fr==0) {P20=0;}
		else {P20=1;du=100;}
	}else{
		div=SYS_FREQ/fr;
		if(div<65536/2){
			EE;PWMCKS=0x00;ED;
		}else{
			if(fr<=1000 && fr>100)	{div=10000;}
			if(fr<=100 && fr>10)	{div=1000;}
			if(fr<=10 && fr>1)		{div=100;}

			T2L=65536-div;T2H=(65536-div)>>8;
			EE; PWMCKS = 0x10; ED;
			div=(SYS_FREQ/div)/fr;
		}
		EE;
		PWMC=div;   
		PWM0T2=div*(100-du)/100;
		PWM0CR =0x80;
		ED;
	}  
	return 1;
}
