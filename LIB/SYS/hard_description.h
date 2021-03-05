#ifndef __HARD_DESCRIPTION__
#define __HARD_DESCRIPTION__
#include "M_Head.h"
//
#define DEF_HD_OUT
#define DEF_HD_INSCAN
#define DEF_HD_SEG

#ifdef DEF_HD_OUT
sbit OUT1   =   P3^7;
sbit OUT2   =   P1^6;
#endif

#ifdef DEF_HD_INSCAN
sbit K1     =   P3^6;
sbit K2     =   P3^5;
sbit K3     =   P3^4;
sbit K4     =   P1^5;
sbit IN1    =   P1^7;
sbit IN2    =   P5^4;
sbit YK1    =   P0^0;
sbit YK2    =   P0^1;
sbit YK3    =   P0^2;
sbit YK4    =   P0^3;
#endif

#ifdef DEF_HD_SEG
#define SEG_IO P2
sbit L1     =   P0^3;
sbit L2     =   P0^2;
sbit L3     =   P0^1;  
sbit L4     =   P0^0;
#endif


#endif