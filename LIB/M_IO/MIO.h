#ifndef __MIO_H__
#define __MIO_H__
#include "M_Head.h"
/**/

#define TW 1
#define KL 2
#define GZ 3
#define SX 4


void IO_INIT();
uchar siomode(uchar now_io_mode_1,uchar now_io_mode_2,uchar new_io_mode,uchar Pin);
void set_io_Mode(uchar Port,uchar Pin,uchar IO_Mode);
uchar sioport_mode(uchar io_mode);
void set_io_port_mode(uchar Port,uchar IO_MODE);

void set_io_port(uchar Port,uchar IO_DATA);
void set_io(uchar Port,uchar Pin,uchar IO_Status);


#endif