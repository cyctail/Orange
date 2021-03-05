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
* Description   : �ӿں���
*
* u_char I2C_WriteStr(u_char sla, u_char suba, u_char *s, u_char no)
* u_char I2C_ReadStr(u_char sla, u_char suba, u_char *s, u_char no)

***************************************************************************/

#include <intrins.h>

#include "main.h"

/* �궨�� */
typedef unsigned char	u_char;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

#define I2C_OK		0
#define I2C_ERROR	1
#define I2C_ACK		0
#define I2C_NAK		1

/* ����22.1184M, 1T = (1/22.1184)us */
#define DELAY_1us	23

sbit SDA = P3^5;	/* ģ��I2C���ݴ���λ */
sbit SCL = P3^4;	/* ģ��I2Cʱ�ӿ���λ */

/* �������� */
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
* Description    : ����ӳ�����us, ������10us.
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
* Description    : ����I2C����, ������I2C��ʼ����.
*****************************************************************/ 
static void I2C_Start(void)
{
	/* SDA,SCL��Ϊ��, ׼��������ʼ���� */
	SDA = 1;
	Delay_us(1);
	SCL = 1;
	Delay_us(5);
    
	/* ������ʼ����: SCL��, SDA��->�� */
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
* Description    : ����I2C����,������I2C��������.
*****************************************************************/ 
static void I2C_Stop(void)
{
	/* ��������: SCL��, SDA��->�� */
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
*                  0, ����Ӧ���ź�; 1, ������Ӧ���ź�.
* Return Value   : none
* Global Variable: none
* Description    : ����������Ӧ����Ӧ���ź�, �ɲ���a����.
*****************************************************************/ 
static void I2C_Ack(u_char a)
{
	/* ����Ӧ����Ӧ���ź� */
	if(a == 0)	
	{
		SDA = 0;	/* Ӧ�� */        
	}
	else 
	{
		SDA = 1;	/* ��Ӧ�� */
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
* Parameters     : u_char c, �����͵��ַ�.
* Return Value   : none
* Global Variable: none
* Description    : ����һ���ֽڵ�����.
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
* Return Value   : u_char, ���յ����ַ�.
* Global Variable: none
* Description    : ����һ���ֽڵ�����.
*****************************************************************/ 
static u_char I2C_ReadByte(void)
{
	u_char i,retc=0;
	
	/* ��������Ϊ���뷽ʽ */
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
* Parameters     : u_char sla, �豸��ַ
*                  u_char suba, �豸�ӵ�ַ
*                  u_char *s, ���ݵ�ַ
*                  u_char no, ���ݳ���
* Return Value   : none
* Global Variable: none
* Description    : ������д���ֽ�����.
*****************************************************************/ 
u_char I2C_WriteStr(u_char sla, u_char suba, u_char *s, u_char no)
{
    u_char i,ack;
	
	/* �������� */
    I2C_Start();
	
	/* ����������ַ(W) */
    ack = I2C_WriteByte(sla);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* ���������ӵ�ַ */
    ack = I2C_WriteByte(suba);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* �������� */
    for(i=0; i<no; i++)
    {   
		ack = I2C_WriteByte(*s);	
		if(ack == I2C_NAK)
		{
			return I2C_ERROR;
		}
		s++;
    } 

	/* �������� */
    I2C_Stop();	 
	
    return I2C_OK;
}

/****************************************************************
* Prototype      : u_char I2C_ReadStr()
* Parameters     : u_char sla, �豸��ַ
*                  u_char suba, �豸�ӵ�ַ
*                  u_char *s, ���ݵ�ַ
*                  u_char no, ���ݳ���
* Return Value   : I2C_OK, �ɹ�; I2C_ERROR, ʧ��.
* Global Variable: none
* Description    : ��������ȡ���ֽ�����.
*****************************************************************/ 
u_char I2C_ReadStr(u_char sla, u_char suba, u_char *s, u_char no)
{
    u_char i,ack;
	
	/* �������� */
    I2C_Start();
	
	/* ����������ַ(W) */
    ack = I2C_WriteByte(sla);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* ���������ӵ�ַ */
    ack = I2C_WriteByte(suba);	
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* ������������ */
    I2C_Start();	
	
	/* ����������ַ(R) */
    ack = I2C_WriteByte(sla+1);
    if(ack == I2C_NAK)
	{
		return I2C_ERROR;
	}

	/* �������ݲ�Ӧ�� */
    for(i=0; i<(no-1); i++)
    {   
		*s = I2C_ReadByte();
		I2C_Ack(0);
		s++;
    } 

	/* ���һ���ֽ�, ��Ӧ�� */
    *s = I2C_ReadByte();
    I2C_Ack(1);

	/* �������� */
    I2C_Stop();			 

    return I2C_OK;
}

