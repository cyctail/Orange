#include "Scanf.h"

#ifdef DEF_IN_SCANF
bit	IN1_Now,IN1_L;
bit	IN2_Now,IN2_L; 
#if USE_KEY_TICK
uint xdata IN1_NT,IN1_OT;
uint xdata IN2_NT,IN2_OT;
#endif
void	Scanf_IN(){	
	IN1_L = IN1_Now;	IN1_Now = IN1;//检测输入 
	IN2_L = IN2_Now;	IN2_Now = IN2;//检测输入 
	//Scan_RF();
	#if USE_KEY_TICK
	if(IN1_NT<60000)IN1_NT++;
	if(IN2_NT<60000)IN2_NT++;
	if(IN1_PRESS || IN1_LEASE){IN1_OT=IN1_NT;IN1_NT=0;}
	if(IN2_PRESS || IN2_LEASE){IN2_OT=IN2_NT;IN2_NT=0;}
	#endif
}
#endif

#ifdef DEF_YK_SCANF
bit YK1_L,YK1_Now;
bit YK2_L,YK2_Now;
bit YK3_L,YK3_Now;
bit YK4_L,YK4_Now;
void Scan_RF(){
////	switch(Get_Key()){
////		case 1: YK1=0;YK2=1;YK3=1;YK4=1; break;
////		case 2: YK1=1;YK2=0;YK3=1;YK4=1; break;
////		case 3: YK1=1;YK2=1;YK3=0;YK4=1; break;
////		case 4: YK1=1;YK2=1;YK3=1;YK4=0; break;
////		default: YK1=1;YK2=1;YK3=1;YK4=1; break;
////	}
	YK1_L = YK1_Now;	YK1_Now = YK1;//检测输入 
	YK2_L = YK2_Now;	YK2_Now = YK2;//检测输入 
	YK3_L = YK3_Now;	YK3_Now = YK3;//检测输入 
	YK4_L = YK4_Now;	YK4_Now = YK4;//检测输入 
}
#endif


#ifdef DEF_KEY_SCANF
bit KEY1 ,KEY_1;
bit KEY2 ,KEY_2;
bit KEY3 ,KEY_3;
bit KEY4 ,KEY_4;
#if USE_KEY_TICK
uint xdata KEY1_NT,KEY1_OT;
uint xdata KEY2_NT,KEY2_OT;
uint xdata KEY3_NT,KEY3_OT;
uint xdata KEY4_NT,KEY4_OT;
#endif
void Scanf_KEY(){
	KEY_1 = KEY1;	KEY1 =K1;
	KEY_2 = KEY2;	KEY2 =K2;
	KEY_3 = KEY3;	KEY3 =K3;
	KEY_4 = KEY4;	KEY4 =K4;
	
	
	#if USE_KEY_TICK
	if(KEY1_NT<60000)KEY1_NT++;
	if(KEY2_NT<60000)KEY2_NT++;
	if(KEY3_NT<60000)KEY3_NT++;
	if(KEY4_NT<60000)KEY4_NT++;
	if(K1_PRESS || K1_LEASE){KEY1_OT=KEY1_NT;KEY1_NT=0;}
	if(K2_PRESS || K2_LEASE){KEY2_OT=KEY2_NT;KEY2_NT=0;}
	if(K3_PRESS || K3_LEASE){KEY3_OT=KEY3_NT;KEY3_NT=0;}
	if(K4_PRESS || K4_LEASE){KEY4_OT=KEY4_NT;KEY4_NT=0;}
	#endif
}
#endif
