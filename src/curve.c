#include <math.h>
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


#define T_MAX_SIZE 10
#define T_SIZE 1


PolyCurve* polycurve_create(int size) {
    PolyCurve* curve = malloc(sizeof(*curve));
    curve->points_length = size;
    curve->points = malloc(sizeof(vec2*) * size);
    return curve;
}

void polycurve_destroy(PolyCurve* curve) {
    int i;
    for(i = 0 ; i < curve->points_length ; ++i) {
        free(curve->points[i]);
    }
    free(curve);
}


PolyCurve* curve_multiquadratic(vec2** points, int size) {
    vec2* p0,
        * p1,
        * p2;
    int i,
        t,
        last_segment = size - 3,
        curve_size = (size / 3) * T_MAX_SIZE;

    PolyCurve* curve = polycurve_create(curve_size);

    for(i = 0 ; i < curve_size ; ++i) {
        p0 = points[i];
        p1 = points[i + 1];
        p2 = (i == last_segment) ? points[0] : points[i + 2];

        for(t = 0 ; t <= T_MAX_SIZE ; t += T_SIZE) {
            curve_quadratic(curve->points[i + t], p0, p1, p2, t);
        }
    }
    return curve;
}


PolyCurve* curve_multicubic(vec2** points, int size) {
    vec2* p0,
        * p1,
        * p2,
        * p3;
    int i,
        t,
        last_segment = size - 4,
        curve_size = (size / 4) * T_MAX_SIZE;

    PolyCurve* curve = polycurve_create(curve_size);

    for(i = 0 ; i < curve_size ; ++i) {
        p0 = points[i];
        p1 = points[i + 1];
        p2 = points[i + 2];
        p3 = (i == last_segment) ? points[0] : points[i + 3];

        for(t = 0 ; t <= T_MAX_SIZE ; t += T_SIZE) {
            curve_cubic(curve->points[i + t], p0, p1, p2, p3, t);
        }
    }
    return curve;
}
