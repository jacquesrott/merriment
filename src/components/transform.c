#include <SDL2/SDL.h>
#include <stdlib.h>

#include "transform.h"


Pool* transformpool_create() {
    unsigned int item_size = sizeof(TransformComponent);
    return pool_create(
        item_size,
        MAX_TRANSFORMS,
        (void (*)(void*)) transformcomponent_destroy);
}


static void transformcomponent_refresh(TransformComponent* component) {
    mat4 rotation = m4_rotatez(component->angle),
         translate = m4_translate2(&component->position);
    m4_x_m4(&component->transform, &rotation, &translate);
}


void* transformpool_add(Pool* pool, vec2 position, float angle, vec2 scale) {
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


void transformcomponent_destroy(TransformComponent* component) {
    pool_set_available(component->pool.container, (PoolObject*) component);
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


void transformcomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context) {
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
