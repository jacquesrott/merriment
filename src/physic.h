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

typedef struct {
    vec2 corner[4];
    vec2 axis[2];
    float origin[2];
} ORect2D;


int v2_in_c2(const vec2* v, const Circle2D* c);
int c2_in_c2(const Circle2D* a, const Circle2D* b);
int c2_collide(const Circle2D* a, const Circle2D* b);

ORect2D* or2_create(const vec2* center, float width, float height, float angle);
void or2_destroy(ORect2D* or2);
int or2_collide_or2(const ORect2D* or2, const ORect2D* other);
int or2_collide_c2(const ORect2D* or2, const Circle2D* c);


#endif
