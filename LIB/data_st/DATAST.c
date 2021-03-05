#include "DATAST.h"
struct DATA_STRUCT xdata stl[STL_NUM];
uint STL_HEAD=STL_NULL;
uint STL_TAIL=STL_NULL;

/*�����ʼ��*/
void STL_init(){
    uint i;
    for(i=0;i<STL_NUM;i++){
        stl[i].used=0;
    }
}
/*��ȡһ���յĽڵ�*/
uchar get_null_id(){
    uint i;
    for(i=0;i<STL_NUM;i++){
        if(stl[i].used==0)return i;
    }
	return STL_NULL;
}
/*�ڵ����-�½�*/
uint STL_Add_Tail(){
    uint zc_id;
    if(STL_HEAD==STL_NULL){
        //creat the first st_line
        STL_HEAD=get_null_id();
        stl[STL_HEAD].last_id    =   STL_NULL;
        stl[STL_HEAD].next_id    =   STL_NULL;
        stl[STL_HEAD].used       =   1;
        STL_TAIL                 =   STL_HEAD;
        return STL_HEAD;
    }else{
        //creat next stl
        zc_id=get_null_id();
        stl[zc_id].last_id       =   STL_TAIL;
        stl[STL_TAIL].next_id    =   zc_id;
        stl[zc_id].next_id       =   STL_NULL;
        stl[zc_id].used          =   1;
        STL_TAIL                 =   zc_id;
        return zc_id;
    }
}
/*ɾ��ĳ���ڵ���������*/
void delate_stl_data(sim_id){
    stl[sim_id].last_id  =   STL_NULL;
    stl[sim_id].next_id  =   STL_NULL;
    stl[sim_id].used     =   0;     
    stl[sim_id].mdata    =   0;
}
/*ɾ��ĳ���ڵ�*/
void STL_DEL_ONCE(uint sim_id){
    if(sim_id == STL_HEAD){
        //if delate line_head
        STL_HEAD=stl[STL_HEAD].next_id;
        delate_stl_data(sim_id);
    }else{
        //if delate line_tail
        if(sim_id == STL_TAIL)STL_TAIL=stl[sim_id].last_id;
        //creat a new link
        stl[stl[sim_id].last_id].next_id  =   stl[sim_id].next_id;
        //delate this stl
        delate_stl_data(sim_id);
    }
}
/*���ݱȽ�**Ĭ�ϱȽ�һ��uint���ݣ�����������Ҫ�޸ı���*/
uchar stl_data_cp(uint sim_id,uint fd){
    if(stl[sim_id].mdata == fd){
        return 1;
    }
    return 0;
}
/*����һ������*/
uchar Find_STL_data(uint fd){
    uint i=STL_HEAD;
    while(i != STL_NULL){       //������������
        if(stl_data_cp(i,fd)){
            return 1;
        }
        i=stl[i].next_id;
    }
    return 0;
}
/**/

