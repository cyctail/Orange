
#ifndef __TICKT_H__
#define __TICKT_H__

#ifndef uchar 
#define uchar   unsigned char
#define uint    unsigned int
#endif

#define Tick_Ver 2

//计时通道

#if Tick_Ver==1
struct Tick_struct{
    uint time;
    uint ztime;
    uint Time_Cnt;
    uchar flag;
};
extern struct Tick_struct t1;
uchar Tick_Time(struct Tick_struct* t);
uchar set_tickt(struct Tick_struct* t,uint set_time,uint set_Time_Cnt,uchar set_flag);

#endif
#if Tick_Ver==2
#define TICK_NUM 10
struct Tick_Str{
	uint time;
	uint Time_Cnt;
	uint hour;
	uint min;
	uint sec;
	uchar flag;
	uchar T_ENABLE;
	uchar T_SUCCESS;
};
extern struct Tick_Str xdata Ts[TICK_NUM];

#define TSTOP		0
#define TRUN		1
#define TPAUSE		2


#define USE_GET_TIME 0
#if USE_GET_TIME
#define GTIME	1
#define GHOUR	2
#define GMIN 	3
#define GSEC 	4
#define GTTIME 	5
uint Get_Time(uchar sim_id,uchar get_stat);
#endif


uchar READ_T(uchar i);
void _SIM_ISR(uchar i);
uchar ISR_Tick_Time(struct Tick_Str* t);
uchar Set_SIM_TICK(uchar sim_id,uint stime,uint sshi,uint sfen,uint smiao,uint sttime_cnt,uchar sflag,uchar OPEN);
uchar get_TS(uchar sim_id);
void set_TS(uchar sim_id,uchar T_stat);
uchar get_Tid();
void use_test();
#endif

#endif