#include "Mode1.h"
uchar set_dis(){
	uchar i;
	for(i=0;i<TICK_NUM;i++){
		if(get_TS(i)==TRUN){SEG_N=Ts[i].time;f_flag=Ts[i].flag;w1=10+i;return 1;}
	}
    return 0;
}
/**/
void  Mode1(){
	if(IN1_PRESS){
		Set_SIM_TICK(0,NULL,NULL,NULL,6,0,4,TRUN);
		OUT1=ON;
	}
	if(READ_T(0)){
		OUT1=OFF;
	}
	set_dis();
}


