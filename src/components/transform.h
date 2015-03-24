#ifndef DW_TRANSFORM_COMPONENT_H
#define DW_TRANSFORM_COMPONENT_H

#include "../config.h"
#include "../pool.h"
#include "../almath.h"
#include "../entity.h"
#include "../cmp.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    vec2 position;
    float angle;
    vec2 scale;
    mat4 transform;
} TransformComponent;


Pool* transformpool_create();
void* transformpool_add(Pool* pool, vec2 position, float angle, vec2 scale);

void transformcomponent_destroy(TransformComponent* component);
void transformcomponent_serialize(TransformComponent* component, cmp_ctx_t* context);
void transformcomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context);


#endif
