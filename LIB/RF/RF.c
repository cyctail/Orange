#include "main.h" //

#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
#ifndef ulong
#define ulong unsigned long
#endif



#define RF_HEAD_MIN 90
#define RF_HEAD_MAX 130
//-
#define RF_0_MIN 1
#define RF_0_MAX 8
//-
#define RF_1_MIN 10
#define RF_1_MAX 20

//-
#define RF_DATA_LENGHT 24
// bit RF_IO;                          //模拟IO口
sbit RF_IO = P3^2;

bit RF_last_flag;                   //上一个电平状态标志位
uint RF_tick;                       //电平时间暂存器
uint RF_low_time;                   //高低电平时间

uchar xdata RF_analysis_stat=0;   //接收电平解析流程暂存
ulong xdata RF_data;            //接收遥控数据暂存
uchar RF_rnum;                  //已接收电平数量
/*供外部使用变量*/
bit RF_K;               //按键状态<虚拟>
#define RF_K_KEEP 200
uchar RF_delay;         //按键状态持续时间
uchar RF_same_key;      //相同KEY_N次数暂存          
/*供外部使用变量*/
ulong xdata RF_ID;            //ID
uchar RF_KEY;           //KEY_N


#define RF_SAVE_NUM 3
ulong xdata RF_SAVE_ID[RF_SAVE_NUM];


/*仅获取单电平信息*/
uchar Tick_RF(){
    if(RF_IO){
        if(!RF_last_flag){
            RF_low_time = RF_tick;
            RF_last_flag = 1;
			return 1;
        }
    }else{
        if(RF_last_flag){
            RF_tick = 0;
            RF_last_flag = 0;
        }
    }
    if(RF_tick<65535)RF_tick++;
    return 0;
}
/*
*解析RF字节数据
**整组数据传输完成后返回 1
**遥控码值存储在 RF_data 中
*/
uchar Analysis_RF(){//RF_analysis_stat=1;
    switch(RF_analysis_stat){
        case 0: 
            if(RF_low_time>=RF_HEAD_MIN){// && RF_low_time<=RF_HEAD_MAX
                RF_analysis_stat=1;
                RF_rnum=0;//ccvvbb=1;
            }
        break;
        case 1: 
            if(RF_low_time>=RF_0_MIN && RF_low_time<=RF_0_MAX){
                RF_data = (RF_data<<1)+1;
                RF_rnum++;
            }else if(RF_low_time>=RF_1_MIN && RF_low_time<=RF_1_MAX){
                RF_data = (RF_data<<1);
                RF_rnum++;
            }else{//数据均不正确，接收复位
                RF_rnum=0;RF_analysis_stat=0;
            }
            if(RF_rnum>=RF_DATA_LENGHT){    //数据接收完成，复位
                RF_rnum=0;RF_analysis_stat=0;
                return 1;
            }
        break;
    }
    return 0;
}
/*校验 KEY 值*/
uchar Proof_RF(uchar RK){
    if(RK==0x01)return 1;
    if(RK==0x02)return 1;
    if(RK==0x04)return 1;
    if(RK==0x08)return 1;
    return 0;
}
/*拆分码值*/
void Split_RF(ulong RF_Sdata){
    RF_ID = (RF_Sdata&0x00fffff0);
    RF_KEY = (uchar)(RF_Sdata&0x0000000f);
}
/*设置遥控按键按下*/
void RF_Press(){
    RF_K = 1;RF_delay = 0;
}
/*设置遥控按键松开*/
void RF_Lease(){
    RF_K = 0;RF_delay = 0;
}


/**/
uchar RF_cmp_timesRF_cmp_times=0;
bit RF_learn=0;
uchar RF_HLEARN=0;
uchar RF_compart(){

    if(RF_ID == RF_SAVE_ID[RF_cmp_timesRF_cmp_times])return 1;        //保留上一次的结果，长时间按下时减少资源消耗（也许）

    for(RF_cmp_timesRF_cmp_times=0;RF_cmp_timesRF_cmp_times<RF_HLEARN;RF_cmp_timesRF_cmp_times++){
        if((RF_ID) == RF_SAVE_ID[1])return 1;
    }
    return 0;
}
/*
**调用函数
***使用环境：定时器中断 <优先级高>
***定时 x_us
*/
void _RF_ISR(){
    if(++RF_delay>RF_K_KEEP){       //按键持续时间，使长按时按键能够保持到下一次按键接收成功
        RF_Lease();
    }
    if(Tick_RF()){//--获得一次电平变化信号的电平长度
        if(Analysis_RF()){//--至此获得一个完整的码值
            Split_RF(RF_data);      //--拆分信号，获得 ID 和 KEY_N
            if(Proof_RF(RF_KEY)){RF_same_key++;}else RF_same_key=0;   //校验 KEY_N,同时提供变量 RF_same_key 用于校验
            if(RF_same_key>=2){RF_same_key=0;       //如果同一个按键持续检测 N 次，即判定为按键正确
                if(RF_learn){RF_learn=0;
                    RF_SAVE_ID[RF_HLEARN++] = RF_ID;
                }else{
                    if(RF_compart())RF_Press();
                }  
            }
        }
    }
}

/*
*获取遥控按键 <供外部使用>
**按键判断没有按下时也返回 0
*/
uchar Get_Key(){
    if(RF_KEY == 0x01)RF_learn=1;
    if(RF_K){
        // if(RF_compart){
            switch(RF_KEY){
                case 0x01: return 1; break;
                case 0x02: return 2; break;
                case 0x04: return 3; break;
                case 0x08: return 4; break;
            }
        // }
    }
    return 0;
}