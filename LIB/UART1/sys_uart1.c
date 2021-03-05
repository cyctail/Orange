#include "main.h"
//#include "muart.h"
#include "intrins.h"

#define FOSC            11059200UL
#define BRT             (65536 - FOSC / 9600 / 4)

bit busy;
uchar xdata buffer[16];
uchar xdata wptr;

char putchar(char c){
	UartSend(c);
	return c;
}

void UartIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
				UART_Analysis(SBUF);
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
    }
}

void UartInit()
{
    SCON = 0x50;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR |= 0x15;
    wptr = 0x00;
    busy = 0;
    ES = 1;
    EA = 1;
}

void UartSend(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

void UartSendStr(char *p)
{
    while (*p)
    {
        UartSend(*p++);
    }
}


