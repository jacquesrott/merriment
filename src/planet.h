#ifndef DW_PLANET_H
#define DW_PLANET_H

typedef struct {
    PolyCurve* curve;
} Planet;


Planet* planet_create();
void planet_destroy(Planet* planet);

#endif
