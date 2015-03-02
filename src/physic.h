#ifndef DW_PHYSIC_H
#define DW_PHYSIC_H

#include <chipmunk/chipmunk.h>

#include "almath.h"
#include "curve.h"


typedef struct {
    vec2 position;
    float radius;
} Circle2D;


int v2_in_c2(const vec2* v, const Circle2D* c);
int c2_in_c2(const Circle2D* a, const Circle2D* b);
int c2_collide(const Circle2D* a, const Circle2D* b);

void polycurve_get_shape(PolyCurve* curve, cpSpace* space, cpBody* body);


#endif
