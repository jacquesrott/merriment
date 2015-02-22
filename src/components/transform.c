#include <stdlib.h>

#include "transform.h"


static void transformcomponent_refresh(TransformCompoment* component) {
    mat4 rotation = m4_rotatez(component->angle),
         translate = m4_translate2(&component->position);
    m4_x_m4(&component->transform, &rotation, &translate);
}


TransformCompoment* transformcomponent_create(vec2 position, float angle) { 
    TransformCompoment* component = malloc(sizeof(*component));
    component->position = position;
    component->angle = angle;
    transformcomponent_refresh(component);
    return component;
}


void transformcomponent_destroy(TransformCompoment* component) {
    free(component);
}
