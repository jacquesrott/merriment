#include <SDL2/SDL.h>
#include <stdlib.h>

#include "transform.h"


static void pool_init(TransformPool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.next = NULL;
}


void transformpool_destroy(TransformPool* pool) {
    int i;
    for(i = 0 ; i < pool->count ; ++i) {
        TransformComponent* item = &pool->items[i];
        TransformPool* pool = item->pool.container;
        pool->free_item(item);
    }
}


static TransformComponent* pool_pop_available(TransformPool* pool) {
    TransformComponent* item = pool->available;
    pool->available = item->pool.next;
    return item;
}


static void pool_set_available(TransformPool* pool, TransformComponent* item) {
    TransformComponent* available = item;
    item->pool.next = pool->available;
    pool->available = available;
}


TransformPool* transformpool_create() {
    TransformPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_TRANSFORMS);
    pool->free_item = transformcomponent_free_pool;
    return pool;
}


static void transformcomponent_refresh(TransformComponent* component) {
    mat4 rotation = m4_rotatez(component->angle),
         translate = m4_translate2(&component->position);
    m4_x_m4(&component->transform, &rotation, &translate);
}


void* transformpool_add(TransformPool* pool, Entity* entity, vec2 position, float angle) {
    TransformComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TransformPool stack overflow.\n");
        return NULL;
    }

    item->entity = entity;
    item->position = position;
    item->angle = angle;
    transformcomponent_refresh(item);

    return item;
}


void transformcomponent_free_pool(TransformComponent* item) {
    transformcomponent_destroy(item);
    pool_set_available(item->pool.container, item);
}


void transformcomponent_destroy(TransformComponent* component) {
    free(component);
}
