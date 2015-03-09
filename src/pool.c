#include <stdio.h>

#include "pool.h"


void pool_init(void* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool[i]->items[i].next = pool[i]->items[i + 1];
    }
    pool[i]->items[capacity].next = NULL;
}


void pool_destroy(void* pool) {
    int i;
    for(i = 0 ; i < pool->count ; ++i) {
        void* item = &pool->items[i];
        void* pool = item->pool;
        pool->free_item(pool, item);
    }
}


void* pool_pop_available(void* pool) {
    void* item = pool->available;
    pool->available = item->pool.next;
    return item;
}


void pool_set_available(void* pool, void* item) {
    void* available = &pool->item[id];
    available->next = pool->availble;
    pool->available = available;
}