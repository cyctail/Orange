#include"tm1650.h"

		

void I2CStart(void)	//��ʼ�ź�
{
	CLK_H;
	DIO_H;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DIO_L;
	
}

void I2Cask(void) //ACK�ź�
{
	uchar timeout = 1;
	CLK_H;
	_nop_();
	_nop_();
	_nop_();
	CLK_L;
	while((DIO)&&(timeout<=100))
	{
	  timeout++;	
	}
	_nop_();
	_nop_();
	_nop_();
	CLK_L;
}

void I2CStop(void) //ֹͣ�ź�
{
	CLK_H;
	DIO_L;
	_nop_();
	_nop_();
	_nop_();
	DIO_H;
}

void I2CWrByte(uchar oneByte) //дһ���ֽڸ�λ��ǰ����λ�ں�
{
	uchar i;
	CLK_L;
	_nop_();
	for(i=0;i<8;i++)
	{	
		oneByte = oneByte<<1;
		DIO = CY;
		CLK_L;
		_nop_();
		_nop_();
		_nop_();
		CLK_H;
		_nop_();
		_nop_();
		_nop_();
		CLK_L;
	}
}

uchar Scan_K(void)	  // ����ɨ��
{
	uchar i;
	uchar rekey;
	I2CStart();
	I2CWrByte(0x49);//����������
	I2Cask();
	//DIO_H;
	for(i=0;i<8;i++)
	{
	   CLK_H;
	   rekey = rekey<<1;
	   if(DIO)
	   {
	   	rekey++;
	   } 
	   _nop_();
	   _nop_();
	   CLK_L;	
	}
	I2Cask();
	I2CStop();
	return(rekey);
}


void TM1650_Set(uchar add,uchar dat) //�������ʾ
{
	//д�Դ����Ӹߵ�ַ��ʼд
	I2CStart();
	I2CWrByte(add); //��һ���Դ��ַ
	I2Cask();
	I2CWrByte(dat);
	I2Cask();
	I2CStop();
}
