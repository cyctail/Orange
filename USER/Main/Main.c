/*
*                           ___________
*                         /            \
*                        \____________/
*                        |           |
*                       /            \
*                     /              \
*                    |               |
*                   |               |
*                  |               |
*                 |               |
*                 \______________/
*                 -----------------  
*/

#include "main.h"

/**/
void F_ITEM(){
	Scanf_KEY();
	Scanf_KEY();
	Scanf_IN();
	Scanf_IN();
}
/**/
void SYS_INIT(){
	IO_INIT();
	set_io_port_mode(2,TW);
	OSAL_INIT();
}
/**/
void main(){
	SYS_INIT();
	DATA_INIT();
	F_ITEM();
	OSAL_FUNCTION();	//F_RUN
} //mian()

