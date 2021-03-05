#ifndef __MUART_H
#define __MUART_H


#ifndef uchar 
#define uchar unsigned char
#endif
#ifndef uint 
#define uint unsigned int
#endif

#define UART_R_num 50

extern bit UART_REFLAG;
extern uchar xdata re_data[UART_R_num];

void UART_Analysis(uchar gbuf);
void cls_buf();
uchar Analysisi_Data(uchar anls[]);



extern uchar xdata UFunc[10];
extern ulong xdata UData;

#endif