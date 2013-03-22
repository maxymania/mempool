#ifndef MEM_POOL_H_INCLUDED
#define MEM_POOL_H_INCLUDED

#include <stdint.h>

typedef struct {
    uint32_t* tpool;
    uint32_t tlength;
    uint32_t curcur;
} MPool;

void MPool_Init(MPool* pool,void* block,uint32_t length);
void *MPool_Allocate(MPool* pool,uint32_t length);
void MPool_Free(MPool* pool,void* buf);
void MPool_Collectfree(MPool* pool);

void MPool_Ex_Tryshrink(MPool* pool,void* buf,uint32_t nlength);
char MPool_Ex_Trygrow(MPool* pool,void* buf,uint32_t nlength);
void MPool_Ex_FreeCleanup(MPool* pool,void* buf);
void *MPool_Ex_AllocJoin(MPool* pool,uint32_t length);
void MPool_Ex_ResetAllocCursor(MPool* pool);

#endif // MEM_POOL_H_INCLUDED
