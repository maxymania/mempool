#include <stdlib.h>
#include "mem_pool.h"

#define USED 0x80000000
#define MASK 0x7fffffff

void MPool_Init(MPool* pool,void* block,uint32_t length){
    pool->tpool=block;
    pool->tlength=length/4;
    pool->curcur=0;
    pool->tpool[0]=(pool->tlength)&MASK;
}
void *MPool_Allocate(MPool* pool,uint32_t length){
    uint32_t curcur,lng,plen;
    lng = (length+7)/4; // (length/4 with round up always) +1
    curcur=pool->curcur;
    while(curcur<pool->tlength){
        plen=(pool->tpool[curcur]);
        if(!(plen&USED))
        if(plen>=lng)
        {
            if(plen>lng){
                pool->tpool[curcur+lng]=plen-lng;
                pool->tpool[curcur]=lng;
                pool->curcur=curcur+lng;
            }else{
                pool->curcur=curcur+plen;
            }
            pool->tpool[curcur]|=USED;
            return &(pool->tpool[curcur+1]);
        }
        curcur+=((pool->tpool[curcur])&MASK);
    }
    return NULL;
}
void MPool_Free(MPool* pool,void* buf){
    uint32_t* unit=buf;
    unit[-1]&=MASK;
}
void MPool_Collectfree(MPool* pool){
    uint32_t cur,first,nwcc;
    char ok,nwcc_set;
    pool->curcur=0;
    cur=0;
    first=0;
    ok=0;
    nwcc=0; // new curcur
    nwcc_set=0;
    while(cur<(pool->tlength)){
        if(pool->tpool[cur]&USED){
            ok=0;
        }else{
            if(!nwcc_set){nwcc_set=1;nwcc=cur;}
            if(ok){
                pool->tpool[first] =
                    (pool->tpool[first]&MASK) +
                    (pool->tpool[cur]&MASK);
            }else{ ok=1; first=cur; }
        }
        cur+=(pool->tpool[cur]&MASK);
    }
    pool->curcur=nwcc;
}

// xxx
