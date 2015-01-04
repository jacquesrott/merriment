#include <math.h>

#include "physic.h"


int v2_in_c2(const vec2* v, const Circle2D* c) {
    vec2 dir;
    v2_m_v2(&dir, v, &c->position);
    float l = v2_length(&dir);
    return (l < c->radius) ? 0 : 1;
}


int c2_in_c2(const Circle2D* a, const Circle2D* b) {
    vec2 dir;
    dir.x = (a->position.x + a->radius) - (b->position.x + b->radius);
    dir.y = (a->position.y + a->radius) - (b->position.y + b->radius);
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
