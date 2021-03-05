#ifndef _DLPWM_H_
#define _DLPWM_H_
  
#include "STC8F.h"

#define SYS_FREQ 27000000UL //系统工作主频率。Hz

extern unsigned long freq;
extern unsigned char dute;
//=============================================================================
extern void PWM_init(void);
extern unsigned  long PWM_set(unsigned long freq,unsigned int dute);

#endif