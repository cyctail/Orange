
#include "scankey.h"

#define SINT uint
#define S_ADD 1
#define S_DEL 0
SINT SET_NUM(SINT now_num,SINT MAX_NUN,SINT MIN_NUM,SINT ADD_NUM,uchar AOD){
	switch(AOD){
		case S_ADD: if(now_num<=(MAX_NUN-ADD_NUM)){now_num+=ADD_NUM;}else{now_num=MIN_NUM;} break;
		case S_DEL: if(now_num>=(MIN_NUM+ADD_NUM)){now_num-=ADD_NUM;}else{now_num=MAX_NUN;} break;
	}
	return now_num;
}


uchar K1_Long_Press;
void Scankey(void){
	if(K1_KEEP_PRESS){
		if(++K1_Long_Press>10){
			Set_W=MODE_USE;
		}
	}else K1_Long_Press=0;
	
	if(K1_PRESS && Set_W>0){
		Set_W=SET_NUM(Set_W,TIME_NUM+1,0,1,S_ADD);
		if(Set_W==0){DATA_SAVE_FLAG=1;}
	}
	
	if(K2_KEEP_PRESS){
		switch(Set_W){
			case 0: break;
			case 1: Mode=SET_NUM(Mode,MODE_NUM,1,1,S_ADD); break;
			default:time_x[Set_W-1]=SET_NUM(time_x[Set_W-1],999,0,1,S_ADD); break;
		}
	}
	
	if(K3_KEEP_PRESS){
		switch(Set_W){
			case 0: break;
			case 1: Mode=SET_NUM(Mode,MODE_NUM,1,1,S_DEL); break;
			default:time_x[Set_W-1]=SET_NUM(time_x[Set_W-1],999,0,1,S_DEL); break;
		}
	}
	if(K4_PRESS){
		switch(Set_W){
			case 0: LED_ONF=SET_NUM(LED_ONF,1,0,1,S_ADD);DATA_SAVE_FLAG=1; break;
			case 1: break;
			default:flag_x[Set_W-1]=SET_NUM(flag_x[Set_W-1],3,0,1,S_ADD); break;
		}
	}
}