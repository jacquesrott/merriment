#ifndef DW_TRANSFORM_COMPONENT_H
#define DW_TRANSFORM_COMPONENT_H

#include "../config.h"
#include "../pool.h"
#include "../almath.h"
#include "../entity.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    vec2 position;
    float angle;
    mat4 transform;
} TransformComponent;


typedef struct {
    TransformComponent items[MAX_TRANSFORMS];
    TransformComponent* available;
    unsigned int count;
} TransformPool;


TransformPool* transformpool_create();
void* transformpool_add(TransformPool* pool, Entity* entity, vec2 position, float angle);
void transformpool_destroy(TransformPool* pool);

void transformcomponent_free_pool(TransformComponent* item);
void transformcomponent_destroy(TransformComponent* component);


#endif
