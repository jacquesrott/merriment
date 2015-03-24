#ifndef DW_POOL_H
#define DW_POOL_H


typedef struct Pool Pool;


typedef struct {
    void* next;
    void* previous;
    Pool* container;
} PoolItem;


typedef struct {
    PoolItem pool;
} PoolObject;


struct Pool{
    void* allocated;
    void* available;
    unsigned int count;
    void (*item_destroy)(void* item);
    unsigned int item_size;
    unsigned int capacity;
    PoolObject* items;
};


Pool* pool_create(unsigned int item_size, unsigned int capacity, void (*destroy)(void* item));
void pool_destroy(Pool* pool);

void* pool_pop_available(Pool* pool);
void pool_set_available(Pool* pool, PoolObject* item);

#endif
