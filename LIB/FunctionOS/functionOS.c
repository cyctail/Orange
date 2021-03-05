#include "FunctionOS.h"

/**/
void SCANKEY_OSU(){
	Scanf_KEY();
	Scankey();
}
/**/
void SEG_SET_OSU(){
	switch(Set_W){
		case 0: 
			if(set_dis()){
				w2=SEG_N%1000/100;w3=SEG_N%100/10;w4=SEG_N%10;
			}else{
				w1=_NET;w2=_NET;w3=_NET;w4=_NET;f_flag=2;
			}
		break;
		case 1: w1=_P;w2=_NET;w3=_NET;w4=Mode;f_flag=2; break;
		case 2: SEG_F_T1(Set_W+8,time_x[Set_W-1],0);f_flag=flag_x[Set_W-1];break;
	}
	if(LED_ONF)Led(w1,w2,w3,w4,f_flag);
	else {Led(_TAP,_TAP,_TAP,_TAP,2);}
}
/**/
void MODE_OSU(){
	if(Set_W==0){
		Scanf_IN();
		Mode1();
	}
}
