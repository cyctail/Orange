/*
*                           ___________
*                         /            \
*                        \____________/
*                        |           |
*                       /            \
*                     /              \
*                    |               |
*                   |               |
*                  |----------_----|
*                 |   --   -      |
*                 \______________/
*                 -----------------  
*/
#include "OSAL.h"
/*
该结构占用了定时器0用作任务轮询，但依旧可以用它来完成计时任务
添加新任务时，需要在TASK_ENUM添加任务名
struct OSL_struct _funtion[enum_max]中初始化任务

*任务入口函数需要在头文件中引用
*/
struct OSL_struct;
uchar OSL_i,OSL_j;
/*
下转struct OSL_struct _funtion[enum_max]初始化任务
*/
enum TASK_ENUM{
	enum_scankey,
	enum_seg,
	enum_mode,
	enum_save,
	enum_max
};
/*
计数初始值
计数最大值
任务触发位
函数指针 <函数需要在头文件中引用>
*/
struct OSL_struct _funtion[enum_max]={
	{0,100,0,SCANKEY_OSU},
	{0,5,0,SEG_SET_OSU},
	{0,5,0,MODE_OSU},
	{0,10,0,DATA_SAVE}
};
/**/
void t0(void) interrupt 1 
{
	#if Tick_Ver==2
	uchar a;
	#endif
	WDT_CONTR=0x35;//喂狗
	#if Tick_Ver==2
	for(a=0;a<TICK_NUM;a++){	//遍历各路计时
		_SIM_ISR(a);			//考虑是否再开一个定时器中.........................................
	}
	#endif
	for(OSL_i=0;OSL_i<enum_max;OSL_i++){
		if(!_funtion[OSL_i].use_flag){
			if( _funtion[OSL_i].OSL_ALL_tick==(++_funtion[OSL_i].OSL_NOW_tick)){
				_funtion[OSL_i].OSL_NOW_tick=0;
				_funtion[OSL_i].use_flag=1;
			}
		}
	}
}
/**/
void Timer0Init(void){     //1毫秒@11.0592MHz
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	WDT_CONTR=0x35;//喂狗 
}
/**/
void OSAL_INIT(){
	Timer0Init(); 
}
/**/
void OSAL_FUNCTION(){
	while(1){
		for(OSL_j=0;OSL_j<enum_max;OSL_j++){
			if(_funtion[OSL_j].use_flag){
				_funtion[OSL_j].FUNCTION();
				_funtion[OSL_j].use_flag=0;
			}
		}
	}
}

