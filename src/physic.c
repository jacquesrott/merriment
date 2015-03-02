#include <math.h>
#include <stdlib.h>

#include "physic.h"


int v2_in_c2(const vec2* v, const Circle2D* c) {
    vec2 dir;
    v2_m_v2(&dir, v, &c->position);
    float l = v2_length(&dir);
    return (l < c->radius) ? 0 : 1;
}


int c2_in_c2(const Circle2D* a, const Circle2D* b) {
    if(a->radius > b->radius) return 1;
    vec2 dir;
    v2_m_v2(&dir, &b->position, &a->position);
    float l = v2_length(&dir);
    float r = fabs(b->radius - a->radius);
    return (l <= r) ? 0 : 1;
}


int c2_collide(const Circle2D* a, const Circle2D* b) {
    vec2 dir;
    v2_m_v2(&dir, &b->position, &a->position);
    float l = (dir.x * dir.x) + (dir.y * dir.y);
    float r = (a->radius + b->radius) * (a->radius + b->radius);
    return (l < r) ? 0 : 1;
}


void polycurve_get_shape(PolyCurve* curve, cpSpace* space, cpBody* body) {
    int i;
    for(i = 0 ; i < curve->points_length - 1 ; ++i) {
        cpVect a = {curve->points[i].x, curve->points[i].y},
               b = {curve->points[i+1].x, curve->points[i+1].y};
        cpShape* segment = cpSegmentShapeNew(body, a, b, 0.0);
        cpSpaceAddShape(space, segment);
    }
}
