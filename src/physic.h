#ifndef DW_PHYSIC_H
#define DW_PHYSIC_H

#include "almath.h"


typedef struct {
    vec2 position;
    float radius;
} Circle2D;


typedef struct {
    vec2 position;
    float width;
    float height;
} Rect2D;


int v2_in_c2(const vec2* v, const Circle2D* c);
int c2_in_c2(const Circle2D* a, const Circle2D* b);
int c2_collide(const Circle2D* a, const Circle2D* b);


#endif
