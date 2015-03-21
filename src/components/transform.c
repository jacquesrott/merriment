#include <SDL2/SDL.h>
#include <stdlib.h>

#include "transform.h"


static void pool_init(TransformPool* pool, unsigned int capacity) {
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


void transformpool_destroy(TransformPool* pool) {
    TransformComponent* item = pool->allocated;
    while(item) {
        TransformComponent* next = item->pool.next;
        transformcomponent_free_pool(item);
        item = next;
    }
    free(pool);
}


static TransformComponent* pool_pop_available(TransformPool* pool) {
    TransformComponent* item = pool->available;
    pool->available = item->pool.next;

    item->pool.next = pool->allocated;
    pool->allocated = item;
    item->pool.previous = NULL;
    ++pool->count;
    return item;
}


static void pool_set_available(TransformPool* pool, TransformComponent* item) {
    TransformComponent* previous = item->pool.previous;
    TransformComponent* next = item->pool.next;

    if(pool->allocated == item) pool->allocated = next;
    if(next != NULL) next->pool.previous = previous;
    if(previous != NULL) previous->pool.next = next;

    item->pool.next = pool->available;
    pool->available = item;
    --pool->count;
}


TransformPool* transformpool_create() {
    TransformPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_TRANSFORMS);
    return pool;
}


static void transformcomponent_refresh(TransformComponent* component) {
    mat4 rotation = m4_rotatez(component->angle),
         translate = m4_translate2(&component->position);
    m4_x_m4(&component->transform, &rotation, &translate);
}


void* transformpool_add(TransformPool* pool, vec2 position, float angle, vec2 scale) {
    TransformComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TransformPool stack overflow.\n");
        return NULL;
    }

    item->component = NULL;
    item->position = position;
    item->angle = angle;
    item->scale = scale;
    transformcomponent_refresh(item);

    return item;
}


void transformcomponent_free_pool(TransformComponent* item) {
    pool_set_available(item->pool.container, item);
}


static void v2_serialize(cmp_ctx_t* context, vec2* v) {
    cmp_write_array(context, 2);

    cmp_write_float(context, v->x);
    cmp_write_float(context, v->y);
}


static void v2_deserialize(cmp_ctx_t* context, vec2* v) {
    uint32_t size;
    cmp_read_array(context, &size);

    if(size != 2) {
        return;
    }
    cmp_read_float(context, &v->x);
    cmp_read_float(context, &v->y);
}


void transformcomponent_serialize(TransformComponent* component, cmp_ctx_t* context) {
    cmp_write_map(context, 3);

    cmp_write_str(context, "angle", 5);
    cmp_write_float(context, component->angle);

    cmp_write_str(context, "position", 8);
    v2_serialize(context, &component->position);

    cmp_write_str(context, "scale", 5);
    v2_serialize(context, &component->scale);
}


void transformcomponent_deserialize(Entity* entity, TransformPool* pool, cmp_ctx_t* context) {
    vec2 position = {0, 0};
    float angle = 0.0;
    vec2 scale = {1, 1};

    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("angle", key) == 0) {
            cmp_read_float(context, &angle);
        } else if(strcmp("scale", key) == 0) {
            v2_deserialize(context, &scale);
        } else if(strcmp("position", key) == 0) {
            v2_deserialize(context, &scale);
        }
    }

    TransformComponent* component = transformpool_add(pool, position, angle, scale);
    ComponentItem* item = componentlist_push(&entity->components, component, TRANSFORM, entity);
    component->component = item;
}
