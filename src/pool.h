#ifndef DW_POOL_H
#define DW_POOL_H


void pool_init(void* pool, unsigned int capacity);
void pool_destroy(void* pool);

void* pool_get_available(void* pool);
void pool_set_available(void* pool, void* item);


#endif