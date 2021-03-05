#ifndef __SCANF_H
#define __SCANF_H

#include "hard_description.h"

#define DEF_KEY_SCANF
#define DEF_IN_SCANF
#define DEF_YK_SCANF
#define USE_KEY_TICK 0


#ifdef DEF_KEY_SCANF
#ifndef DEF_HD_INSCAN
sbit K1=P3^6;
sbit K2=P3^5;
sbit K3=P3^4;
sbit K4=P1^5;
#endif
extern bit KEY1 ,KEY_1;
extern bit KEY2 ,KEY_2;
extern bit KEY3 ,KEY_3;
extern bit KEY4 ,KEY_4;
#if USE_KEY_TICK
extern uint xdata KEY1_NT,KEY1_OT;
extern uint xdata KEY2_NT,KEY2_OT;
extern uint xdata KEY3_NT,KEY3_OT;
extern uint xdata KEY4_NT,KEY4_OT;
#endif

#define KEY_TURE    0
#define KEY_FAULT   1

#define K1_LEASE        ((KEY_1==KEY_TURE )&&(KEY1==KEY_FAULT))
#define K1_PRESS        ((KEY_1==KEY_FAULT)&&(KEY1==KEY_TURE ))
#define K1_KEEP_PRESS 	 (K1==KEY_TURE )
#define K1_KEEP_LEASE 	 (K1==KEY_FAULT)

#define K2_LEASE        ((KEY_2==KEY_TURE )&&(KEY2==KEY_FAULT))
#define K2_PRESS        ((KEY_2==KEY_FAULT)&&(KEY2==KEY_TURE ))
#define K2_KEEP_PRESS 	 (K2==KEY_TURE )
#define K2_KEEP_LEASE 	 (K2==KEY_FAULT)

#define K3_LEASE        ((KEY_3==KEY_TURE )&&(KEY3==KEY_FAULT))
#define K3_PRESS        ((KEY_3==KEY_FAULT)&&(KEY3==KEY_TURE ))
#define K3_KEEP_PRESS 	 (K3==KEY_TURE )
#define K3_KEEP_LEASE 	 (K3==KEY_FAULT)

#define K4_LEASE        ((KEY_4==KEY_TURE )&&(KEY4==KEY_FAULT))
#define K4_PRESS        ((KEY_4==KEY_FAULT)&&(KEY4==KEY_TURE ))
#define K4_KEEP_PRESS 	 (K4==KEY_TURE )
#define K4_KEEP_LEASE 	 (K4==KEY_FAULT)
void Scanf_KEY();
#endif


#ifdef DEF_IN_SCANF
#ifndef DEF_HD_INSCAN
sbit IN1 = P1^7;
sbit IN2 = P5^4;
#endif
extern bit	IN1_Now,IN1_L;
extern bit	IN2_Now,IN2_L;
#if USE_KEY_TICK
extern uint xdata IN1_NT,IN1_OT;
extern uint xdata IN2_NT,IN2_OT;
#endif
#define IN_TURE     0
#define IN_FAULT    1

#define IN1_LEASE	    ((IN1_L==IN_TURE )&&(IN1_Now==IN_FAULT))
#define IN1_PRESS	    ((IN1_L==IN_FAULT)&&(IN1_Now==IN_TURE ))
#define IN1_KEEP_PRESS 	 (IN1==IN_TURE )
#define IN1_KEEP_LEASE 	 (IN1==IN_FAULT)

#define IN2_LEASE       ((IN2_L==IN_TURE )&&(IN2_Now==IN_FAULT))
#define IN2_PRESS	    ((IN2_L==IN_FAULT)&&(IN2_Now==IN_TURE ))
#define IN2_KEEP_PRESS 	 (IN2==IN_TURE )
#define IN2_KEEP_LEASE 	 (IN2==IN_FAULT)
void Scanf_IN();
#endif


#ifdef DEF_YK_SCANF
#ifndef DEF_HD_INSCAN
sbit YK1=P0^0;
sbit YK2=P0^1;
sbit YK3=P0^2;
sbit YK4=P0^3;
#endif
extern bit YK1_L,YK1_Now;
extern bit YK2_L,YK2_Now;
extern bit YK3_L,YK3_Now;
extern bit YK4_L,YK4_Now;
#define YK_TURE     0
#define YK_FAULT    1
#define YK1_LEASE        ((YK1_L==YK_TURE )&&(YK1_Now==YK_FAULT))
#define YK1_PRESS	     ((YK1_L==YK_FAULT)&&(YK1_Now==YK_TURE))
#define YK1_KEEP_PRESS 	 (YK1_Now==YK_TURE)
#define YK1_KEEP_LEASE 	 (YK1_Now==YK_FAULT)

#define YK2_LEASE        ((YK2_L==YK_TURE )&&(YK2_Now==YK_FAULT))
#define YK2_PRESS	     ((YK2_L==YK_FAULT)&&(YK2_Now==YK_TURE))
#define YK2_KEEP_PRESS 	 (YK2_Now==YK_TURE)
#define YK2_KEEP_LEASE 	 (YK2_Now==YK_FAULT)

#define YK3_LEASE        ((YK3_L==YK_TURE)&&(YK3_Now==YK_FAULT))
#define YK3_PRESS	     ((YK3_L==YK_FAULT)&&(YK3_Now==YK_TURE))
#define YK3_KEEP_PRESS 	 (YK3_Now==YK_TURE)
#define YK3_KEEP_LEASE 	 (YK3_Now==YK_FAULT)

#define YK4_LEASE        ((YK4_L==YK_TURE)&&(YK4_Now==YK_FAULT))
#define YK4_PRESS	     ((YK4_L==YK_FAULT)&&(YK4_Now==YK_TURE))
#define YK4_KEEP_PRESS 	 (YK4_Now==YK_TURE)
#define YK4_KEEP_LEASE 	 (YK4_Now==YK_FAULT)
void Scan_RF();
#endif

#endif