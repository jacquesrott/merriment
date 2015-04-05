#include <stdlib.h>
#include <stdio.h>

#include "pool.h"


Pool* pool_create(unsigned int item_size, unsigned int capacity, void (*destroy)(void* item)) {
    Pool* pool = malloc(sizeof(*pool));
    pool->item_destroy = destroy;
    pool->item_size = item_size;

    pool->capacity = capacity;

    unsigned int pool_size = item_size * capacity;
    pool->items = malloc(pool_size);

    PoolObject* first_item = &pool->items[0];
    PoolObject* last_item = (PoolObject*) (((char*) first_item) + pool_size - item_size);

    pool->available = first_item;
    pool->allocated = NULL;

    PoolObject* item;
    for(item = first_item ; item < last_item; item = (PoolObject*) ((char*) item + item_size)) {
        item->pool.container = pool;
        item->pool.previous = NULL;
        item->pool.next = ((char*) item) + item_size;
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
