#ifndef __OSAL_H_
#define __OSAL_H_

#include "main.h"
/**/
struct OSL_struct{
	uint OSL_NOW_tick;
	uint OSL_ALL_tick;
	uint use_flag;
	void (*FUNCTION)();
};
extern struct OSL_struct;
extern void OSAL_INIT();
extern void OSAL_FUNCTION();

#endif