#ifndef __DATAST_H__
#define __DATAST_H__

#ifndef uchar 
#define uchar unsigned char 
#endif
#ifndef uint 
#define uint unsigned int 
#endif
#ifndef ulong 
#define ulong unsigned long 
#endif

#define STL_NUM 100
#define STL_NULL STL_NUM

struct DATA_STRUCT{
    uchar used;
    uchar next_id;
    uchar last_id;
    uint mdata;
};
extern struct DATA_STRUCT xdata stl[STL_NUM];


void STL_init();
uint STL_Add_Tail();
void STL_DEL_ONCE(uint sim_id);
uchar Find_STL_data(uint fd);
#endif