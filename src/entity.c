#include <SDL2/SDL.h>
#include <stdlib.h>

#include "entity.h"
#include "pool.h"


static void pool_init(EntityPool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    pool->allocated = NULL;
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.container = pool;
        pool->items[i].pool.previous = NULL;
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.container = pool;
    pool->items[capacity].pool.previous = NULL;
    pool->items[capacity].pool.next = NULL;
    pool->count = 0;
}


void entitypool_destroy(EntityPool* pool) {
    Entity* item = pool->allocated;
    while(item) {
        Entity* next = item->pool.next;
        entity_destroy(item);
        item = next;
    }
    free(pool);
}


static Entity* pool_pop_available(EntityPool* pool) {
    Entity* item = pool->available;
    pool->available = item->pool.next;

    item->pool.next = pool->allocated;
    pool->allocated = item;
    item->pool.previous = NULL;
    ++pool->count;
    return item;
}


static void pool_set_available(EntityPool* pool, Entity* item) {
    Entity* previous = item->pool.previous;
    Entity* next = item->pool.next;

    if(pool->allocated == item) pool->allocated = next;
    if(next != NULL) next->pool.previous = previous;
    if(previous != NULL) previous->pool.next = next;

    item->pool.next = pool->available;
    pool->available = item;
    --pool->count;
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


void entity_serialize(Entity* entity, Scene* scene, cmp_ctx_t* context) {
    cmp_write_map(context, 2);

    cmp_write_str(context, "name", 4);
    cmp_write_str(context, entity->name, strlen(entity->name));

    cmp_write_str(context, "components", 10);
    cmp_write_array(context, entity->components.count);

    ComponentItem* component = entity->components.head;

    while(component != NULL) {
        component_serialize(component, entity, scene, context);
        component = component->next;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity `%s` serialized.\n", entity->name);
}


void entity_deserialize(Entity* entity, Scene* scene, cmp_ctx_t* context) {
    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("name", key) == 0) {
            uint32_t name_len = 65;
            cmp_read_str(context, entity->name, &name_len);
            entity->name[name_len] = 0;
        } else if(strcmp("components", key) == 0) {
            uint32_t components_size;
            cmp_read_array(context, &components_size);

            int i;
            for(i = 0 ; i < components_size ; ++i) {
                component_deserialize(entity, scene, context);
            }
        }
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity `%s` deserialized.\n", entity->name);
}
