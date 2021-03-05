#include "time1.h"


/*定时器1*/
void Timer1_Init(){
	TMOD = 0x00;		//模式0
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xAE;			//65536-11.0592M/12/1000
	TH1 = 0xFB;
	TR1 = 1;			//启动定时器
	ET1 = 1;			//使能定时器中断
	EA = 1;
}

/**/
#if TIMER1	
void TM1_Isr() interrupt 3
{
}
#endif
