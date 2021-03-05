#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "M_Head.h"
#include <intrins.h>
/*后续追加*/
sfr IAP_TPS = 0xF5;
/********************************************************************
                            命令定义
*********************************************************************/
#define CMD_IDLE     0	    //EEPROM无操作
#define CMD_READ     1	    //读取字节
#define CMD_PROGRAM  2	    //写入字节
#define CMD_ERASE    3	    //擦除字节
/********************************************************************
                       编程周期由晶振决定
*********************************************************************/
//#define ENABLE_IAP 0X80	 //编程周期由晶振决定（如果<30MHZ选用此项）
//#define ENABLE_IAP 0X81	 //编程周期由晶振决定（如果<24MHZ选用此项）
//#define ENABLE_IAP 0X82	 //编程周期由晶振决定（如果<20MHZ选用此项）
  #define ENABLE_IAP 0X83	 //编程周期由晶振决定（如果<12MHZ选用此项）
//#define ENABLE_IAP 0X84	 //编程周期由晶振决定（如果<6MHZ选用此项）
//#define ENABLE_IAP 0X85	 //编程周期由晶振决定（如果<3MHZ选用此项）
//#define ENABLE_IAP 0X86	 //编程周期由晶振决定（如果<2MHZ选用此项）
//#define ENABLE_IAP 0X87	 //编程周期由晶振决定（如果<1MHZ选用此项）

#define IAP_ADDRESS 0X0000	 //内部EEPROM地址
/********************************************************************
                            开机最大次数和最长时间定义
*********************************************************************/

/*********************************************************************/
void IapIdle();				              //操作函数
uchar IapReadByte(uint addr);             //读取函数
void IapProgramByte(uint addr,uchar dat); //写入函数
void IapEraseSector(uint addr);	          //擦除函数
//============================================================
#endif