/*2018.5.18
Ƶ�� ��1HZ��150KHZ�ɵ���ռ�ձȣ�0��100% �ٷ�֮һ�ɵ�
STC8F2K08S2-SSOP20
����STC8A8Kϵ���еĸ߾���PWMģ��+TIMER2��Ϊ��Ƶ����δʹ���ж�

2018.5.25
����STC8A8K64S4A12-LQFP48
����STC8A8Kϵ���е�15bit��ǿ��PWMģ��+TIMER2��Ϊ��Ƶ����δʹ���ж�
*/

#include "PWM.h"
#include "INTRINS.H"

unsigned char dute=50;
unsigned long freq=1*1000;

#define EE P_SW2|=0x80  //ʹ�ܷ���XSFR
#define ED P_SW2&=~0x80 //���ܷ���XSFR

void PWM_init(void){  	//��ʱ��2�̶�Ϊ16λ�Զ�����
	AUXR&=~8;//��ʱ��
	AUXR|=4;//1Tģʽ
	T2L=65536-1000;T2H=(65536-1000)>>8;

	PWMCFG = 0x00;                  //����PWM�������ʼ��ƽΪ�͵�ƽ
	P2M0=P2M1=0;//����Ϊ�����

	EE;  
	PWMCKS = 0x10;                  //ѡ��PWM��ʱ��ΪT2����ʣ��üĴ�����Ƶ��Ч��
	PWMC = 1000;                    //����PWM����
	PWM0T1=0x0000;                  //����PWM2��1�η�ת��PWM����
	PWM0T2=SYS_FREQ/27000 * 50 / 100;      //����PWM2��2�η�ת��PWM����
										//ռ�ձ�Ϊ(PWM0T2-PWM0T1)/PWMC
	PWM0CR =0x80; //���ʹ�ܣ���ʼ�͵�ƽ,�����ж�
	ED;            
	PWMCR = 0xc0;  
	AUXR|=0x10;                     //������ʱ��2
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
