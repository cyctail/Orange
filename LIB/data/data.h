#ifndef __DATA_H__
#define __DATA_H__
#include "main.h"
/*参数设置*/
#define TIME_NUM 2
#define MODE_USE 2
#define MODE_NUM 2

/**/
#define ON	0
#define OFF	1
/**/
#define EPR_ADDR_0 0x0000
#define EPR_ADDR_2 0x0200
#define EPR_ADDR_4 0x0400
#define EPR_ADDR_8 0x0800

#ifndef DEF_HD_OUT
sbit OUT1 = P3^7;
sbit OUT2 = P1^6;
#endif

extern uint     xdata time_x[TIME_NUM+1];
extern uchar    xdata flag_x[TIME_NUM+1];

extern uchar    xdata LED_ONF;
extern uint     xdata SEG_N;
extern uchar    xdata Mode;
extern uchar    xdata Set_W;
extern uchar    xdata stat_mode;
extern bit      DATA_SAVE_FLAG;


void DATA_INIT();
void DATA_SAVE();
#endif