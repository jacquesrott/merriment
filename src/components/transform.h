#ifndef DW_TRANSFORM_COMPONENT_H
#define DW_TRANSFORM_COMPONENT_H

typedef struct TransformCompoment TransformCompoment;

#include "../almath.h"
#include "../entity.h"

struct TransformCompoment {
    vec2 position;
    float angle;
    mat4 transform;
};


TransformCompoment* transformcomponent_create(vec2 position, float angle);
void transformcomponent_destroy(TransformCompoment* component);


#endif
