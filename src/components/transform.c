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
    pool->count = 0;
}


void transformpool_destroy(TransformPool* pool) {
    TransformComponent* item = pool->allocated;
    while(item) {
        transformcomponent_free_pool(item);
        item = item->pool.next;
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

    if(next) next->pool.previous = previous;
    if(previous) previous->pool.next = next;

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
    transformcomponent_destroy(item);
    pool_set_available(item->pool.container, item);
}


void transformcomponent_destroy(TransformComponent* component) {
    free(component);
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

    TransformComponent* transform = transformpool_add(pool, position, angle, scale);
    componentlist_push(&entity->components, transform, TRANSFORM, entity);
}
