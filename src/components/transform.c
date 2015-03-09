#include <stdlib.h>

#include "transform.h"


TransformPool* transformpool_create() {
    TransformPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_SPRITES);
    pool->free = transformpool_free;
    return pool;
}


static void transformcomponent_refresh(TransformCompoment* component) {
    mat4 rotation = m4_rotatez(component->angle),
         translate = m4_translate2(&component->position);
    m4_x_m4(&component->transform, &rotation, &translate);
}


void* transformpool_add(TransformPool* pool, Entity* entity, vec2 position, float angle) {
    TransformComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TransformPool stack overflow.\n", name);
        return NULL;
    }

    item->entity = entity;
    item->position = position;
    item->angle = angle;
    transformcomponent_refresh(item);

    return item;
}


void transformpool_free(TransformPool* pool, TransformComponent* item) {
    transformcomponent_destroy(item);
    pool_set_available(pool, item);
}


void transformcomponent_destroy(TransformCompoment* component) {
    free(component);
}
