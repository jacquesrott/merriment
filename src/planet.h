#ifndef DW_PLANET_H
#define DW_PLANET_H

#include "almath.h"
#include "curve.h"
#include "mesh.h"


typedef struct {
    mat4 transform;
    float radius;
    Mesh* mesh;
    PolyCurve* curve;
} Planet;


Planet* planet_create();
void planet_generate(Planet* planet);
void planet_destroy(Planet* planet);

#endif
