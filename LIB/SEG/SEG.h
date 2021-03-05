
#include "hard_description.h"


#ifndef DEF_HD_SEG
#define SEG_IO P2
sbit L1=P0^3;
sbit L2=P0^2;
sbit L3=P0^1;  
sbit L4=P0^0;
#endif

extern uchar xdata f_flag;
extern uchar xdata w1,w2,w3,w4;

#define Word_0  0
#define Word_1  1
#define Word_2  2
#define Word_3  3
#define Word_4  4
#define Word_5  5
#define Word_6  6
#define Word_7  7
#define Word_8  8
#define Word_9  9
#define Word_A  10
#define Word_b  11
#define Word_C  12
#define Word_d  13

#define _P	    14
#define _NET    _P+1
#define _TAP    _NET+1

void Led(uchar a,uchar b,uchar c,uchar d,uchar seg_flag);
void SEG_F_T1(uchar seg_head,uint seg_data,uchar fnum);

