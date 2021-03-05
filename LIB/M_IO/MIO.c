#include "MIO.h"
// #include "STC8F.H"


uchar xdata zc_io_mode1,zc_io_mode2;
/**/
void IO_INIT(){
	set_io_Mode(0,0,SX);
	set_io_port_mode(0,SX);
	set_io(2,0,0);
	set_io_port(2,0);
    P0M0=P0M1=0x00;
    P1M0=P1M1=0x00;
    P2M0=P2M1=0x00;
    P3M0=P3M1=0x00;
    P4M0=P4M1=0x00;
    P5M0=P5M1=0x00;
    P6M0=P6M1=0x00;
    P7M0=P7M1=0x00;
}
/**/
void set_io(uchar Port,uchar Pin,uchar IO_Status){
    switch(Port){
        case 0: if(IO_Status)P0 |= 0x01<<Pin; else P0 &= ~(0x01<<Pin); break;
        case 1: if(IO_Status)P1 |= 0x01<<Pin; else P1 &= ~(0x01<<Pin); break;
        case 2: if(IO_Status)P2 |= 0x01<<Pin; else P2 &= ~(0x01<<Pin); break;
        case 3: if(IO_Status)P3 |= 0x01<<Pin; else P3 &= ~(0x01<<Pin); break;
        case 4: if(IO_Status)P4 |= 0x01<<Pin; else P4 &= ~(0x01<<Pin); break;
        case 5: if(IO_Status)P5 |= 0x01<<Pin; else P5 &= ~(0x01<<Pin); break;
        case 6: if(IO_Status)P6 |= 0x01<<Pin; else P6 &= ~(0x01<<Pin); break;
        case 7: if(IO_Status)P7 |= 0x01<<Pin; else P7 &= ~(0x01<<Pin); break;
    }
}
/**/
void set_io_port(uchar Port,uchar IO_DATA){
    switch(Port){
        case 0: P0=IO_DATA; break;
        case 1: P1=IO_DATA; break;
        case 2: P2=IO_DATA; break;
        case 3: P3=IO_DATA; break;
        case 4: P4=IO_DATA; break;
        case 5: P5=IO_DATA; break;
        case 6: P6=IO_DATA; break;
        case 7: P7=IO_DATA; break;
    }
}
/**/
uchar siomode(uchar now_io_mode_1,uchar now_io_mode_2,uchar new_io_mode,uchar Pin){
    switch(new_io_mode){
        case SX: now_io_mode_1 &= ~(0x01<<Pin);now_io_mode_2 &= ~(0x01<<Pin); break;  //00
        case TW: now_io_mode_1 |=  (0x01<<Pin);now_io_mode_2 &= ~(0x01<<Pin); break;  //10
        case KL: now_io_mode_1 |=  (0x01<<Pin);now_io_mode_2 |=  (0x01<<Pin); break;  //11
        case GZ: now_io_mode_1 &= ~(0x01<<Pin);now_io_mode_2 |=  (0x01<<Pin); break;  //01
        default: return 0; break;
    }
    zc_io_mode1=now_io_mode_1;zc_io_mode2=now_io_mode_2;
    return 1;
}
/**/
void set_io_Mode(uchar Port,uchar Pin,uchar IO_Mode){
    switch(Port){
        case 0: if(siomode(P0M0,P0M1,IO_Mode,Pin)){P0M0=zc_io_mode1;P0M1=zc_io_mode2;} break;
        case 1: if(siomode(P1M0,P1M1,IO_Mode,Pin)){P1M0=zc_io_mode1;P1M1=zc_io_mode2;} break;
        case 2: if(siomode(P2M0,P2M1,IO_Mode,Pin)){P2M0=zc_io_mode1;P2M1=zc_io_mode2;} break;
        case 3: if(siomode(P3M0,P3M1,IO_Mode,Pin)){P3M0=zc_io_mode1;P3M1=zc_io_mode2;} break;
        case 4: if(siomode(P4M0,P4M1,IO_Mode,Pin)){P4M0=zc_io_mode1;P4M1=zc_io_mode2;} break;
        case 5: if(siomode(P5M0,P5M1,IO_Mode,Pin)){P5M0=zc_io_mode1;P5M1=zc_io_mode2;} break;
        case 6: if(siomode(P6M0,P6M1,IO_Mode,Pin)){P6M0=zc_io_mode1;P6M1=zc_io_mode2;} break;
        case 7: if(siomode(P7M0,P7M1,IO_Mode,Pin)){P7M0=zc_io_mode1;P7M1=zc_io_mode2;} break;
    }
}
/**/
uchar sioport_mode(uchar io_mode){
    switch(io_mode){
        case SX: zc_io_mode1=0x00;zc_io_mode2=0x00; break;  //00
        case TW: zc_io_mode1=0xff;zc_io_mode2=0x00; break;  //10
        case KL: zc_io_mode1=0xff;zc_io_mode2=0xff; break;  //11
        case GZ: zc_io_mode1=0x00;zc_io_mode2=0xff; break;  //01
        default: return 0; break;
    }
    return 1;
}
/**/
void set_io_port_mode(uchar Port,uchar IO_MODE){
    if(sioport_mode(IO_MODE)){
        switch(Port){
            case 0: P0M0=zc_io_mode1;P0M1=zc_io_mode2;break;
            case 1: P1M0=zc_io_mode1;P1M1=zc_io_mode2;break;
            case 2: P2M0=zc_io_mode1;P2M1=zc_io_mode2;break;
            case 3: P3M0=zc_io_mode1;P3M1=zc_io_mode2;break;
            case 4: P4M0=zc_io_mode1;P4M1=zc_io_mode2;break;
            case 5: P5M0=zc_io_mode1;P5M1=zc_io_mode2;break;
            case 6: P6M0=zc_io_mode1;P6M1=zc_io_mode2;break;
            case 7: P7M0=zc_io_mode1;P7M1=zc_io_mode2;break;
        }
    }
}
//

