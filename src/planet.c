#include <time.h>
#include <stdlib.h>

#include "planet.h"
#include "random.h"
#include "config.h"


Planet* planet_create() {
    Planet* planet = malloc(sizeof(*planet));
    planet->radius = 0;

    return planet;
}


void planet_destroy(Planet* planet) {
    polycurve_destroy(planet->curve);
    free(planet);
}


void planet_generate(Planet* planet) {
    srandom(time(NULL));
}
