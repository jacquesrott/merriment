#ifndef DW_POOL_H
#define DW_POOL_H


typedef struct {
    void* next;
    void* previous;
    void* container;
} PoolItem;


#endif
