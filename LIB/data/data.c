#include "data.h"


uint	xdata time_x[TIME_NUM+1];   
uchar	xdata flag_x[TIME_NUM+1];

uchar   xdata LED_ONF=1;
uint    xdata SEG_N=0;
uchar   xdata Mode=0;
uchar   xdata Set_W=0;
uchar   xdata stat_mode=0;
bit     DATA_SAVE_FLAG=0;



uchar xdata epr;
/**/
void DATA_INIT(){
	Mode		= IapReadByte(EPR_ADDR_0+1);
	LED_ONF	= IapReadByte(EPR_ADDR_0+2);
	
	for(epr=0;epr<TIME_NUM;epr++){
		time_x[epr+1]=(IapReadByte(EPR_ADDR_2+epr*2)<<8)+IapReadByte(EPR_ADDR_2+1+epr*2);
	}
	for(epr=0;epr<TIME_NUM;epr++){
		flag_x[epr+1]=IapReadByte(EPR_ADDR_2+TIME_NUM*2+epr);
	}
	
	if(Mode==0x00 || Mode==0xff){
		Mode=1;LED_ONF=1;
		for(epr=0;epr<TIME_NUM;epr++){
			time_x[epr+1]=1;
		}
		for(epr=0;epr<TIME_NUM;epr++){
			flag_x[epr+1]=1;
		}
		time_x[1]=P2M0;
	}
}
/**/
void DATA_SAVE(){
	if(DATA_SAVE_FLAG){DATA_SAVE_FLAG=0;
		IapEraseSector(EPR_ADDR_0);
		IapProgramByte(EPR_ADDR_0+1,Mode);
		IapProgramByte(EPR_ADDR_0+2,LED_ONF);
		
		IapEraseSector(EPR_ADDR_2);
		for(epr=0;epr<TIME_NUM;epr++){
			IapProgramByte(EPR_ADDR_2+epr*2,time_x[epr+1]>>8);
			IapProgramByte(EPR_ADDR_2+1+epr*2,time_x[epr+1]);
		}
		for(epr=0;epr<TIME_NUM;epr++){
			IapProgramByte(EPR_ADDR_2+TIME_NUM*2+epr,flag_x[epr+1]);
		}
	}
}
