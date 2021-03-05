#include "MMath.h"
#include "stdlib.h"
#define US_GET_RANDOM 0

#if US_GET_RANDOM
uint R_Seed;
uint get_new_seed(){
    R_Seed+=17;
    return R_Seed;
}
//
uint get_Random(uint Random_Max,uint Random_Min){
    srand(R_Seed);
    R_Seed=(R_Seed%65500)+7;
    return rand()%(Random_Max-Random_Min)+Random_Min;
}
#endif