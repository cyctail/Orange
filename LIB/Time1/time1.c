#include "time1.h"


/*��ʱ��1*/
void Timer1_Init(){
	TMOD = 0x00;		//ģʽ0
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xAE;			//65536-11.0592M/12/1000
	TH1 = 0xFB;
	TR1 = 1;			//������ʱ��
	ET1 = 1;			//ʹ�ܶ�ʱ���ж�
	EA = 1;
}

/**/
#if TIMER1	
void TM1_Isr() interrupt 3
{
}
#endif
