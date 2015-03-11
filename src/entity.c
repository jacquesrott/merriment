#include <SDL2/SDL.h>
#include <stdlib.h>

#include "entity.h"
#include "pool.h"


static void pool_init(EntityPool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.next = NULL;
}


void entitypool_destroy(EntityPool* pool) {
    int i;
    for(i = 0 ; i < pool->count ; ++i) {
        Entity* item = &pool->items[i];
        entity_destroy(item);
    }
}


static Entity* pool_pop_available(EntityPool* pool) {
    Entity* item = pool->available;
    pool->available = item->pool.next;
    return item;
}


static void pool_set_available(EntityPool* pool, Entity* item) {
    Entity* available = item;
    item->pool.next = pool->available;
    pool->available = available;
}


EntityPool* entitypool_create() {
    EntityPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_ENTITIES);
    return pool;
}


void* entitypool_add(EntityPool* pool) {
    Entity* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "EntityPool stack overflow.\n");
        return NULL;
    }

    item->L = luaL_newstate();
    luaL_openlibs(item->L);

    item->components.head = NULL;
    item->components.count = 0;

    return item;
}


void entity_free(Entity* entity) {
    componentlist_clear(&entity->components);
}


void entity_free_pool(Entity* item) {
    entity_free(item);
    entity_destroy(item);
    pool_set_available(item->pool.container, item);
}


void entity_destroy(Entity* entity) {
    lua_close(entity->L);
}
