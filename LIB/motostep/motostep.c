
#include "main.h"
#include "math.h"

/*
*主函数中运行
*speed_flag标志位在定时器中置1
*/
//if(speed_flag){
//	speed_flag=0;
//	if(PWMCR != 0x00){get_Speed();}// && cc==0
//	PWM_set(fr,50);
//}

unsigned long xdata fr;
unsigned long xdata Purse_num,Ln_DOWM,num,V_max,V_min=100;
uchar acceleration=30;

/**/
void get_S_N(){
	uint V;
	unsigned long Sn1,Sn2,Snmax;
	V=V_max-V_min;

	Snmax = Purse_num*2/3/*Purse_num/2*/;					//允许用于加速的最大行程
	Sn1 	= V/acceleration*(V_min+V/2);		//达到最大速度需要的行程
	Sn2 	= Sn1/2 /*Sn1*/;									//减速所需的最小行程

	if(Sn1 > Snmax){
		Ln_DOWM = Snmax;
	}else{
		Ln_DOWM = Purse_num - Sn2;
	}
}
/**/
unsigned long get_sp(){
	return sqrt(4*acceleration*(Purse_num-num)+V_min*V_min);
}
/**/
void get_Speed(){
	// get_S_N();
	if(PWMCR==0x80){
		if(fr < (V_max-acceleration)){
			fr+=acceleration;
		}else if(fr > (V_max+acceleration)){
			fr-=acceleration;
		}else fr=V_max;
	}else if(PWMCR == 0xc0){		//计数模式下

		if(num<=Ln_DOWM){
			if(fr < (V_max-acceleration)){
				fr+=acceleration;
			}else if(fr > (V_max+acceleration)){
				fr-=acceleration;
			}else fr=V_max;
		}else{
			first=0;
			if(fr>=(get_sp()*xf-100)){
				if(fr > V_min){
					fr-=2*acceleration;
				}else fr=V_min;
			}//else fr++;
		}
	}
}
/**/
void Start(uchar x,uchar y){
	DIR = y;	 fr = 1;
	switch(x){
		case 0: PWMCR = 0x80;EN = EN0;  break;
		case 1: num = 0;num = 0;Purse_num=5*(unsigned long)(xf*time_x[2])/4;get_S_N();PWMCR = 0xc0;EN = EN0;  break;
	}
	V_max = 8*xf*time_x[1]/3;
//	PWM_set(1,50);  
	
}
/**/
void Stop(){
	PWMCR = 0x00;EN=EN1;num=0;
}
