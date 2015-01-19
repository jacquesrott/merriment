#ifndef DW_CURVE_H
#define DW_CURVE_H

#include "almath.h"


typedef struct {
    vec2** points;
    int points_length;
} PolyCurve;


vec2* curve_quadratic(vec2* out, const vec2* p0,  const vec2* p1, const vec2* p2, float t);
vec2* curve_cubic(vec2* out, const vec2* p0,  const vec2* p1, const vec2* p2, const vec2* p3, float t);

PolyCurve* curve_multiquadratic(vec2** points, int size);
PolyCurve* curve_multicubic(vec2** points, int size);

PolyCurve* polycurve_create(int size);
void polycurve_destroy(PolyCurve* curve);


#endif
