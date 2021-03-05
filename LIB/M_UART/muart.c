
#include "main.h"


bit UART_REFLAG=0;			//������ɱ�־λ
uchar xdata re_data[UART_R_num]={0};		//�������ݴ洢����
/*单字节数据头接收*/
//#define UART_HEAD '*'
//#define UART_TAIL '#'
//uchar UART_AS=255;
//void UART_Analysis(uchar gbuf){
//	if(UART_TAIL==gbuf){UART_AS=255;UART_REFLAG=1;}
//	if(gbuf!=UART_HEAD && UART_AS<255){
//		re_data[UART_AS++]=gbuf;
//	}
//	if(UART_HEAD==gbuf && UART_REFLAG==0)UART_AS=0;
//}


/**/
void cls_buf(){
	uchar cls_i;
	for(cls_i=0;cls_i<UART_R_num;cls_i++){
		re_data[cls_i]=0;
	}
	UART_REFLAG=0;
}
/*多字节数据头接收*/
#define THEAD_LENGHT 3
uchar UART_THEAD[THEAD_LENGHT] = {'S','T','>'};
#define UART_TTAIL1 '\r'	//数据结束可能是'\r\n'，也有可能是'\n'
#define UART_TTAIL2 '\n'	//只要检测到一个就停止
uchar UART_HEAD_STAT=0;
uchar UART_RET_STAT=0;
bit UART_R_NY=0;
void UART_Analysis(uchar gbuf){		
	if(UART_R_NY){		//已接收正确得数据头，允许接收数据和结束位
		if((gbuf == UART_TTAIL1 || gbuf == UART_TTAIL2) && UART_R_NY){UART_HEAD_STAT=0;UART_R_NY=0;UART_REFLAG=1;re_data[UART_RET_STAT]='#';UART_RET_STAT=0;}		//接收数据结束位
		else re_data[UART_RET_STAT++] = gbuf;		//接收数据
	}
	
	if(UART_THEAD[UART_HEAD_STAT++] == gbuf){		//接收数据头
		if(UART_HEAD_STAT==THEAD_LENGHT){cls_buf();UART_HEAD_STAT=0;UART_R_NY=1;}//接收到正确得数据头，清除数组并开启数据接收
	}else UART_HEAD_STAT=0;
}


/*数据解析*/
uchar xdata UFunc[10]={0};			//第一组数据
uchar xdata UData_JC[10]={0};		//暂存第二组数据的值
ulong xdata UData	= 0;					//第二组数据最后计算的值
uchar Analysisi_Data(uchar anls[]){
	uchar A_D_num=0,A_SD_num=0,ais;
	ulong cs=1;		//
	
	while(anls[A_D_num] != '='){		//找到第一个分隔符，获得第一组数据
		UFunc[A_D_num]=anls[A_D_num];
		if(++A_D_num>=10)return 0;		//数据设限，避免死循环
	}A_D_num++;
	
	while(anls[A_D_num]!='#'){			//找到数据停止位，获得第二组数据
		UData_JC[A_SD_num] = anls[A_D_num];
		A_D_num++;
		if(++A_SD_num>=10)return 0;		//数据设限，避免死循环
	}
	
	UData=0;
	for(ais=A_SD_num;ais>0;ais--){		//转换第二组数据成数值
		if(UData_JC[ais-1]>=(0+'0') && UData_JC[ais-1]<=(9+'0')){	//判断数据是否在正确范围
			UData+=(UData_JC[ais-1]-'0')*cs;		//计算各位置对应数值，从个位开始
			cs=cs*10;
		}else return 0;
	}
	
	return 1;
}
