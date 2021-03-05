#include "eeprom.h"

/********************************************************************
                            操作函数
*********************************************************************/
void IapIdle()
{
	IAP_CONTR=0;
	IAP_CMD=0;
	IAP_TRIG=0;
	IAP_ADDRH=0X80;
	IAP_ADDRL=0;
}
/********************************************************************
                            读取一个字节函数
*********************************************************************/
uchar IapReadByte(uint addr)
{
	uchar dat;  
	IAP_CONTR=ENABLE_IAP;
	IAP_TPS = 12; 
	IAP_CMD=CMD_READ;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
	_nop_();
	_nop_();
	_nop_();
	dat=IAP_DATA;
	IapIdle();
	return dat;
}

/********************************************************************
                            写入一个字节函数
*********************************************************************/
void IapProgramByte(uint addr,uchar dat)
{

	IAP_CONTR=ENABLE_IAP;
	IAP_CMD=CMD_PROGRAM;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_DATA=dat;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
	_nop_();
	_nop_();
	_nop_();
	IapIdle();
}
/********************************************************************
                            擦除一个字节函数
*********************************************************************/
void IapEraseSector(uint addr)
{
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD=CMD_ERASE;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_TRIG=0X5A;
	IAP_TRIG=0XA5;
	_nop_();
	_nop_();
	_nop_();
	IapIdle();
}