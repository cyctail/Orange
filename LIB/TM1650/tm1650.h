#ifndef __TM1650_H__
#define __TM1650_H__
#include"STC8F.h"
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit CLK = P3^1;
sbit DIO = P3^0;


#define CLK_H  CLK = 1
#define CLK_L  CLK = 0

#define DIO_H  DIO = 1
#define DIO_L  DIO = 0

void TM1650_Set(uchar add,uchar dat);
 uchar Scan_K(void);
 #endif