#include"STC8F.h"		//需更换对应的单片机头文件

#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

#define SEG_IO P1

sbit L1=P0^0;
sbit L2=P0^1;
sbit L3=P0^2;  
sbit L4=P0^3;

sbit L8=P0^4;
sbit L7=P0^5;
sbit L6=P0^6;  
sbit L5=P0^7;

extern uchar f_flag1,f_flag2;

extern void Led(uchar led_a1,uchar led_a2,uchar led_a3,uchar led_a4,uchar led_a5,uchar led_a6,uchar led_a7,uchar led_a8);