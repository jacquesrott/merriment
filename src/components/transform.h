#ifndef DW_TRANSFORM_COMPONENT_H
#define DW_TRANSFORM_COMPONENT_H

#include "../config.h"
#include "../pool.h"
#include "../almath.h"
#include "../entity.h"


typedef struct {
    Entity* entity;
    vec2 position;
    float angle;
    mat4 transform;
} TransformCompoment;


typedef struct {
    TransformComponent items[MAX_TRANSFORMS];
    TransformComponent* available;
    unsigned int count;
    void (*free_item)(void* item);
} TransformPool;


TransformPool* transformpool_create();
void* transformpool_add(TransformPool* pool, Entity* entity, vec2 position, float angle);
void transformpool_free(TransformPool* pool, TransformComponent* item);

TransformCompoment* transformcomponent_create(vec2 position, float angle);
void transformcomponent_destroy(TransformCompoment* component);


#endif
