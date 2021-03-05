
#ifndef __SYS_UART_H
#define __SYS_UART_H

#include "STC8F.h"

#ifndef uchar
#define uchar unsigned char
#define uint	unsigned int
#define ulong	unsigned long
#endif

void UartInit();
void UartSend(uchar dat);
void UartSendStr(uchar *p);
//void UART_Analysis(uchar gbuf);
extern uchar xdata buffer[16];

#endif