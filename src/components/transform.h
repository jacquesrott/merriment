#ifndef DW_TRANSFORM_COMPONENT_H
#define DW_TRANSFORM_COMPONENT_H

typedef struct TransformPool TransformPool;

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


struct TransformPool {
    TransformComponent items[MAX_TRANSFORMS];
    TransformComponent* allocated;
    TransformComponent* available;
    unsigned int count;
};


TransformPool* transformpool_create();
void* transformpool_add(TransformPool* pool, vec2 position, float angle, vec2 scale);
void transformpool_destroy(TransformPool* pool);

void transformcomponent_free_pool(TransformComponent* item);
void transformcomponent_destroy(TransformComponent* component);
void transformcomponent_deserialize(Entity* entity, TransformPool* pool, cmp_ctx_t* context);


#endif
