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


void or2_compute_axes(ORect2D* or2) {
    v2_m_v2(&or2->axis[0], &or2->corner[1], &or2->corner[2]);
    v2_m_v2(&or2->axis[1], &or2->corner[3], &or2->corner[0]);

    int a;
    for(a = 0; a < 2; ++a) {
        float squared_length = v2_length(&or2->axis[a]);
        v2_d_f(&or2->axis[a], &or2->axis[a], squared_length);
        or2->origin[a] = v2_dot_v2(&or2->corner[0], &or2->axis[a]);
    }
}


ORect2D* or2_create(const vec2* center, float width, float height, float angle) {
    ORect2D* or2 = malloc(sizeof(*or2));
    float asin = sin(angle),
          acos = cos(angle),
          w_half = width / 2,
          h_half = height / 2;
    vec2 x = { acos * w_half, asin * w_half },
         y = { -asin * h_half, acos * h_half };

    vec2 center_minus_x,
         center_plus_x;
    v2_m_v2(&center_minus_x, center, &x);
    v2_p_v2(&center_plus_x, center, &x);

    v2_m_v2(&or2->corner[0], &center_minus_x, &y);
    v2_m_v2(&or2->corner[1], &center_plus_x, &y);
    v2_p_v2(&or2->corner[2], &center_plus_x, &y);
    v2_p_v2(&or2->corner[3], &center_minus_x, &y);

    or2_compute_axes(or2);

    return or2;
}


void or2_destroy(ORect2D* or2) {
    free(or2);
}


int or2_collide_1way(const ORect2D* or2, const ORect2D* other) {
    int a;
    for(a = 0; a < 2 ; ++a) {
        float t = v2_dot_v2(&other->corner[0], &or2->axis[a]),
              t_min = t,
              t_max = t;
        int c;
        for(c = 1; c < 4 ; ++c) {
            t = v2_dot_v2(&other->corner[c], &or2->axis[a]);
            if(t < t_min) {
                t_min = t;
            } else if(t > t_max) {
                t_max = t;
            }
        }

        if((t_min > 1 + or2->origin[a]) || (t_max < or2->origin[a])) {
            return 1;
        }
    }
    return 0;
}


int or2_collide_or2(const ORect2D* or2, const ORect2D* other) {
    return or2_collide_1way(or2, other) && or2_collide_1way(other, or2);
}


int or2_collide_c2(const ORect2D* or2, const Circle2D* c) {
    return 1;    
}
