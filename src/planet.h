#ifndef DW_PLANET_H
#define DW_PLANET_H

#include <chipmunk/chipmunk.h>

#include "curve.h"
#include "mesh.h"


typedef struct {
    float radius;
    Mesh* mesh;
    PolyCurve* curve;
    cpBody* body;
} Planet;


Planet* planet_create();
void planet_generate(Planet* planet, cpSpace* space);
void planet_destroy(Planet* planet);

#endif
