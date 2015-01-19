#include <stdlib.h>

#include "planet.h"
#include "curve.h"


Planet* planet_create() {
    Planet* planet = malloc(sizeof(*planet));

    return planet;
}


void planet_destroy(Planet* planet) {
    polycurve_destroy(planet->curve);
    free(planet);
}
