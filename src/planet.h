#ifndef DW_PLANET_H
#define DW_PLANET_H

#include "curve.h"
#include "mesh.h"


typedef struct {
    float radius;
    Mesh* mesh;
    PolyCurve* curve;
} Planet;


Planet* planet_create();
void planet_generate(Planet* planet);
void planet_destroy(Planet* planet);

#endif
