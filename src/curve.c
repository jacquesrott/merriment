#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "curve.h"


vec2* curve_quadratic(vec2* out, const vec2* p0,  const vec2* p1, const vec2* p2, float t) {
    out->x = pow(1 - t, 2) * p0->x +
             (1 - t) * 2 * t * p1->x +
             t * t * p2->x;
    out->y = pow(1 - t, 2) * p0->y +
             (1 - t) * 2 * t * p1->y +
             t * t * p2->y;

    return out;
}


vec2* curve_cubic(vec2* out, const vec2* p0,  const vec2* p1, const vec2* p2, const vec2* p3, float t) {
    out->x = pow(1 - t, 3) * p0->x +
             pow(1 - t, 2) * 3 * t * p1->x +
             (1 - t) * 3 * t * t * p2->x +
             t * t * t * p3->x;
    out->y = pow(1 - t, 3) * p0->y +
             pow(1 - t, 2) * 3 * t * p1->y +
             (1 - t) * 3 * t * t * p2->y +
             t * t * t * p3->y;
    return out;
}


#define T_MAX_SIZE 1.0
#define T_SIZE 0.1


PolyCurve* polycurve_create(int size) {
    PolyCurve* curve = malloc(sizeof(*curve));
    curve->points_length = size;
    curve->points = malloc(sizeof(vec2) * size);
    return curve;
}

void polycurve_destroy(PolyCurve* curve) {
    free(curve->points);
    free(curve);
}


PolyCurve* curve_multiquadratic(vec2* points, int size) {
    int i,
        t_counter = 0,
        last_segment = size - 2,
        curve_size = (size / 2) * (T_MAX_SIZE / T_SIZE);
    float t;

    PolyCurve* curve = polycurve_create(curve_size);

    for(i = 0 ; i < size; i += 2) {
        vec2 *p0 = &points[i];
        vec2 *p1 = &points[i + 1];
        vec2 *p2 = (i == last_segment) ? &points[0] : &points[i + 2];

        for(t = 0.0 ; t < T_MAX_SIZE ; t += T_SIZE) {
            curve_quadratic(&curve->points[t_counter], p0, p1, p2, t);
            ++t_counter;
        }
    }
    return curve;
}


PolyCurve* curve_multicubic(vec2* points, int size) {
    int i,
        t_counter = 0,
        last_segment = size - 3,
        curve_size = (size / 3) * (T_MAX_SIZE / T_SIZE);
    float t;

    PolyCurve* curve = polycurve_create(curve_size);

    for(i = 0 ; i < size ; ++i) {
        vec2* p0 = &points[i];
        vec2* p1 = &points[i + 1];
        vec2* p2 = &points[i + 2];
        vec2* p3 = (i == last_segment) ? &points[0] : &points[i + 3];

        for(t = 0 ; t < T_MAX_SIZE ; t += T_SIZE) {
            curve_cubic(&curve->points[t_counter], p0, p1, p2, p3, t);
            ++t_counter;
        }
    }
    return curve;
}
