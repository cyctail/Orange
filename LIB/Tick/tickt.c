#include "tickt.h"

/*_________________^_^___________________*/
#if Tick_Ver==1
struct Tick_struct t1;
/**/
uchar Tick_Time(struct Tick_struct* t){
	if(t->time>0){
		switch(t->flag){
			case 0: if(++t->Time_Cnt>=2)			{t->Time_Cnt=0;t->time--;} break;
			case 1: if(++t->Time_Cnt>=20)			{t->Time_Cnt=0;t->time--;} break;
			case 2: if(++t->Time_Cnt>=200)			{t->Time_Cnt=0;t->time--;} break;
			case 3: if(++t->Time_Cnt>=12000)	    {t->Time_Cnt=0;t->time--;} break;
		}
	}else{
		t->time=0; t->Time_Cnt=0; return 1;
	}
	return 0;
}
/**/
uchar set_tickt(struct Tick_struct* t,uint set_time,uint set_Time_Cnt,uchar set_flag){
    t->time=set_time;
    t->Time_Cnt=set_Time_Cnt;
    t->flag=set_flag;
	return 1;
}
#endif
#if Tick_Ver==2
struct Tick_Str xdata Ts[TICK_NUM];
/*1*/
uchar Set_SIM_TICK(uchar sim_id,uint stime,uint hours,uint mins,uint secs,uint sttime_cnt,uchar sflag,uchar OPEN){
	Ts[sim_id].hour		=	hours;
	Ts[sim_id].min		=	mins;
	Ts[sim_id].sec		=	secs;
	Ts[sim_id].time		=	stime;
	Ts[sim_id].Time_Cnt	=	sttime_cnt;
	Ts[sim_id].flag		=	sflag;
	Ts[sim_id].T_ENABLE	=	OPEN;
	if(OPEN==TRUN)Ts[sim_id].T_SUCCESS=	0;
	return sim_id;
}
/*3*/
uchar ISR_Tick_Time(struct Tick_Str* t){
	if(t->time==0 && t->hour==0 && t->min==0 && t->sec==0){
		return 1;
	}else{
		switch(t->flag){
			case 9:	t->time--; break;												//0.001s
			case 0: if(++t->Time_Cnt>=10)	{t->Time_Cnt=0;t->time--;} break;		//0.01s
			case 1: if(++t->Time_Cnt>=100)	{t->Time_Cnt=0;t->time--;} break;		//0.1s
			case 2: if(++t->Time_Cnt>=1000)	{t->Time_Cnt=0;t->time--;} break;		//1s
			case 3: if(++t->Time_Cnt>=60000){t->Time_Cnt=0;t->time--;} break;		//1min
			case 4: if(++t->Time_Cnt>=1000)	{t->Time_Cnt=0;if(t->sec>0)t->sec--;else{if(t->min>0){t->min--;t->sec=59;}else{return 1;}}} break;		//fen.miao
			case 5: if(++t->Time_Cnt>=60000){t->Time_Cnt=0;if(t->sec>0)t->sec--;else{if(t->hour>0){t->hour--;t->sec=59;}else{return 1;}}} break;	//shi.fen
		}
	}
	return 0;
}
/*2*/
void _SIM_ISR(uchar i){
	if(Ts[i].T_ENABLE==TRUN){
		if(ISR_Tick_Time(&Ts[i])){
			Ts[i].T_ENABLE=TSTOP;
			Ts[i].T_SUCCESS=1;
		}
	}
}
/*UR*/
uchar READ_T(uchar i){
	uchar ret_TF=Ts[i].T_SUCCESS;
	Ts[i].T_SUCCESS=0;
	return ret_TF;
}
/**/
uchar get_TS(uchar sim_id){
	return (Ts[sim_id].T_ENABLE|Ts[sim_id].T_SUCCESS);
}
/**/
void set_TS(uchar sim_id,uchar T_stat){
	Ts[sim_id].T_ENABLE=T_stat;
	Ts[sim_id].T_SUCCESS=0;
}
/**/
#if USE_GET_TIME
uint Get_Time(uchar sim_id,uchar get_stat){
	switch(get_stat){
		case GTIME: 	return Ts[sim_id].time; 	break;
		case GHOUR: 	return Ts[sim_id].hour; 	break;
		case GMIN: 		return Ts[sim_id].min; 		break;
		case GSEC: 		return Ts[sim_id].sec; 		break;
		case GTTIME:	return Ts[sim_id].Time_Cnt;	break;
	}
	return 0;
}
#endif
/**/
uchar get_Tid(){
	uchar i;
	for(i=0;i<TICK_NUM;i++){
		if(Ts[i].T_ENABLE==TSTOP)return i;
	}
	return 255;
}
/**/
void use_test(){
	uchar i;
	set_TS(get_Tid(),get_TS(get_Tid()));
	for(i=0;i<TICK_NUM;i++){
		Ts[i].T_ENABLE=TSTOP;
	}
}
/**/
// void Set_Fan(uchar sim_id,uint stime,uint hours,uint mins,uint secs,uint sttime_cnt,uchar sflag){
// 	switch(sflag){
// 		case 0: Ts[sim_id].Time_Cnt=10-Ts[sim_id].Time_Cnt; 	break;
// 		case 1: Ts[sim_id].Time_Cnt=100-Ts[sim_id].Time_Cnt; 	break;
// 		case 2: Ts[sim_id].Time_Cnt=1000-Ts[sim_id].Time_Cnt; 	break;
// 		case 3: Ts[sim_id].Time_Cnt=60000-Ts[sim_id].Time_Cnt; 	break;
// 		case 4: Ts[sim_id].Time_Cnt=1000-Ts[sim_id].Time_Cnt; 	break;
// 		case 5: Ts[sim_id].Time_Cnt=60000-Ts[sim_id].Time_Cnt; 	break;
// 	}
// 	Ts[sim_id].hour	=	hours-Ts[sim_id].hour;
// 	Ts[sim_id].min	=	mins-Ts[sim_id].min;
// 	Ts[sim_id].sec	=	hours-Ts[sim_id].sec;
// }
/**/
/**/
#endif