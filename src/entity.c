#include <stdlib.h>

#include "entity.h"
#include "pool.h"


EntityPool* entitypool_create() {
    EntityPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_ENTITIES);
    pool->free = entitypool_free;
    return pool;
}


void* entitypool_add(EntityPool* pool) {
    Entity* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "EntityPool stack overflow.\n", name);
        return NULL;
    }

    item->L = luaL_newstate();
    luaL_openlibs(item->L);
    item->components.count = 0;

    return item;
}


void entitypool_free(EntityPool* pool, Entity* item) {
    entity_destroy(item);
    pool_set_available(pool, item);
}


void entity_destroy(Entity* entity) {
    lua_close(entity->L);
    int i;
    for(i = 0 ; i < entity->components.count ; ++i) {
        void* component = entity->components.items[i];
        void* pool = component->pool;
        pool->free_item(pool, component);
    }
    entity->components.count = 0;
}
