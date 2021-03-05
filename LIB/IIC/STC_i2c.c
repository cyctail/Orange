/***************************************************************************
* Module Name   :                                                    
* Identification:                                                  
* Date          :                                           
*                                                                        
* Author        : Yu Lianqing                                           
*                                                                        
* Copyright (c)                          
* ALL RIGHTS RESERVED                                                
*                                                                         
* Revisions of %M% :                                                    
* #.##   Name         Date          Description                        
* ----   ------------ ------------- ----------------------------------- 
*                                                                         
* Description   : 接口函数
*
* u_char I2C_WriteStr(u_char sla, u_char suba, u_char *s, u_char no)
* u_char I2C_ReadStr(u_char sla, u_char suba, u_char *s, u_char no)

***************************************************************************/

#include <intrins.h>

#include "main.h"

/* 宏定义 */
typedef unsigned char	u_char;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

#define I2C_OK		0
#define I2C_ERROR	1
#define I2C_ACK		0
#define I2C_NAK		1

/* 晶振22.1184M, 1T = (1/22.1184)us */
#define DELAY_1us	23

sbit SDA = P3^5;	/* 模拟I2C数据传送位 */
sbit SCL = P3^4;	/* 模拟I2C时钟控制位 */

/* 函数声明 */
static void Delay_us(u_char d);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Ack(u_char a);
static u_char I2C_WriteByte(u_char c);
static u_char I2C_ReadByte(void);

/****************************************************************
* Prototype      : void Delay_us()
* Parameters     : none
* Return Value   : none
* Global Variable: none
* Description    : 软件延迟若干us, 不超过10us.
*****************************************************************/ 
static void Delay_us(u_char d)
{
	u_char i,cnt;

	cnt = d * DELAY_1us;
	for(i=0; i<cnt; i++)
	{
		_nop_();
	}

	return;
}

/****************************************************************
* Prototype      : void I2C_Start()
* Parameters     : none
* Return Value   : none
* Global Variable: none
* Description    : 启动I2C总线, 即发送I2C起始条件.
*****************************************************************/ 
static void I2C_Start(void)
{
	/* SDA,SCL都为高, 准备发送起始条件 */
	SDA = 1;
	Delay_us(1);
	SCL = 1;
	Delay_us(5);
    
	/* 发送起始条件: SCL高, SDA高->低 */
	SDA = 0;
	Delay_us(5);
	SCL = 0;
	Delay_us(2);

	return;
}

/****************************************************************
* Prototype      : void I2C_Stop()
* Parameters     : none
* Return Value   : none
* Global Variable: none
* Description    : 结束I2C总线,即发送I2C结束条件.
*****************************************************************/ 
static void I2C_Stop(void)
{
	/* 结束条件: SCL高, SDA低->高 */
	SDA = 0;
	Delay_us(1);     
	SCL = 1;
	Delay_us(5);
	SDA = 1;
	Delay_us(4);

	return;
}

/****************************************************************
* Prototype      : void I2C_Ack()
* Parameters     : bit a
*                  0, 发出应答信号; 1, 发出非应答信号.
* Return Value   : none
* Global Variable: none
* Description    : 主控器发送应答或非应答信号, 由参数a决定.
*****************************************************************/ 
static void I2C_Ack(u_char a)
{
	/* 发送应答或非应答信号 */
	if(a == 0)	
	{
		SDA = 0;	/* 应答 */        
	}
	else 
	{
		SDA = 1;	/* 非应答 */
	}
	Delay_us(3);      
	SCL = 1;
	Delay_us(5);
	SCL = 0;
	Delay_us(2);    
	
	return;
}

/****************************************************************
* Prototype      : u_char I2C_WriteByte()
* Parameters     : u_char c, 待发送的字符.
* Return Value   : none
* Global Variable: none
* Description    : 发送一个字节的数据.
*****************************************************************/ 
static u_char I2C_WriteByte(u_char c)
{
	u_char i,ack;

	for(i=0; i<8; i++)	
	{
		if((c << i) & 0x80)		
		{
			SDA = 1;    
		}
        else   
		{
			SDA = 0;                
		}
		Delay_us(5);
		SCL = 1;
		Delay_us(5);
		SCL = 0; 
	}
    
	Delay_us(2);
	SDA = 1;
	Delay_us(3);   
	SCL = 1;
	Delay_us(5);

	if(SDA == 1)
	{
		ack = I2C_NAK;     
	}
	else 
	{
		ack = I2C_ACK;		
	}

	SCL = 0;
	Delay_us(2);

	return ack;
}

/****************************************************************
* Prototype      : u_char I2C_ReadByte()
* Parameters     : none
* Return Value   : u_char, 接收到的字符.
* Global Variable: none
* Description    : 接收一个字节的数据.
*****************************************************************/ 
static u_char I2C_ReadByte(void)
{
	u_char i,retc=0;
	
	/* 置数据线为输入方式 */
	SDA = 1;	

	for(i=0; i<8; i++)
	{
//		Delay_us(1);   
		SCL = 0;
		Delay_us(5);
		SCL = 1;
		Delay_us(5);
		retc = retc << 1;
		if(SDA == 1) 
		{
			retc++;
		}
//		Delay_us(2); 
	}

	SCL = 0;    
	Delay_us(5);

	return retc;
}

/****************************************************************
* Prototype      : u_char I2C_WriteStr()
* Parameters     : u_char sla, 设备地址
*                  u_char suba, 设备子地址
*                  u_char *s, 数据地址
*                  u_char no, 数据长度
* Return Value   : none
* Global Variable: none
* Description    : 向器件写多字节数据.
*****************************************************************/ 
u_char I2C_WriteStr(u_char sla, u_char suba, u_char *s, u_char no)
{
    u_char i,ack;
	
	/* 启动总线 */
    I2C_Start();
	
	/* 发送器件地址(W) */
    ack = I2C_WriteByte(sla);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* 发送器件子地址 */
    ack = I2C_WriteByte(suba);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* 发送数据 */
    for(i=0; i<no; i++)
    {   
		ack = I2C_WriteByte(*s);	
		if(ack == I2C_NAK)
		{
			return I2C_ERROR;
		}
		s++;
    } 

	/* 结束总线 */
    I2C_Stop();	 
	
    return I2C_OK;
}

/****************************************************************
* Prototype      : u_char I2C_ReadStr()
* Parameters     : u_char sla, 设备地址
*                  u_char suba, 设备子地址
*                  u_char *s, 数据地址
*                  u_char no, 数据长度
* Return Value   : I2C_OK, 成功; I2C_ERROR, 失败.
* Global Variable: none
* Description    : 从器件读取多字节数据.
*****************************************************************/ 
u_char I2C_ReadStr(u_char sla, u_char suba, u_char *s, u_char no)
{
    u_char i,ack;
	
	/* 启动总线 */
    I2C_Start();
	
	/* 发送器件地址(W) */
    ack = I2C_WriteByte(sla);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* 发送器件子地址 */
    ack = I2C_WriteByte(suba);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* 重新启动总线 */
    I2C_Start();	
	
	/* 发送器件地址(R) */
    ack = I2C_WriteByte(sla+1);
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* 接收数据并应答 */
    for(i=0; i<(no-1); i++)
    {   
		*s = I2C_ReadByte();
		I2C_Ack(0);
		s++;
    } 

	/* 最后一个字节, 非应答 */
    *s = I2C_ReadByte();
    I2C_Ack(1);

	/* 结束总线 */
    I2C_Stop();			 

    return I2C_OK;
}

