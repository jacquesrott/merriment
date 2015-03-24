#include <stdlib.h>
#include <stdio.h>

#include "pool.h"


Pool* pool_create(unsigned int item_size, unsigned int capacity, void (*destroy)(void* item)) {
    Pool* pool = malloc(sizeof(*pool));
    pool->item_destroy = destroy;
    pool->item_size = item_size;

    pool->capacity = capacity;

    unsigned int pool_size = item_size * capacity;

    capacity = capacity - 1;
    pool->items = malloc(item_size * capacity);

    pool->available = &pool->items[0];
    pool->allocated = NULL;
    PoolObject* last_item = pool->items + pool_size;

    PoolObject* item;
    for(item = pool->items ; item < last_item; item += item_size) {
        item->pool.container = pool;
        item->pool.previous = NULL;
        item->pool.next = item + item_size;
    }
    last_item->pool.container = pool;
    last_item->pool.previous = NULL;
    last_item->pool.next = NULL;
    pool->count = 0;

    return pool;
}


void pool_destroy(Pool* pool) {
    PoolObject* item = pool->allocated;
    while(item) {
        PoolObject* next = item->pool.next;
        pool->item_destroy(item);
        item = next;
    }
    free(pool->items);
    free(pool);
}


void* pool_pop_available(Pool* pool) {
    PoolObject* item = pool->available;
    pool->available = item->pool.next;

    item->pool.next = pool->allocated;
    pool->allocated = item;
    item->pool.previous = NULL;
    ++pool->count;
    return item;
}


void pool_set_available(Pool* pool, PoolObject* item) {
    PoolObject* previous = item->pool.previous;
    PoolObject* next = item->pool.next;

    if(pool->allocated == item) pool->allocated = next;
    if(next != NULL) next->pool.previous = previous;
    if(previous != NULL) previous->pool.next = next;

    item->pool.next = pool->available;
    pool->available = item;
    --pool->count;
}
