#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "almath.h"
#include "planet.h"
#include "random.h"
#include "config.h"


Planet* planet_create() {
    Planet* planet = malloc(sizeof(*planet));
    planet->radius = 0.0;

    return planet;
}


void planet_destroy(Planet* planet) {
    polycurve_destroy(planet->curve);
    mesh_destroy(planet->mesh);
    free(planet);
}


void* array_concat(void* out, const void* a, size_t a_size, const void* b, size_t b_size) {
    memcpy(out, a, a_size);
    memcpy(out + a_size, b, b_size);
    return out;
}


void planet_generate(Planet* planet) {
    int max_points = 360;
    int counter = 0;
    float angle;

    vec2 points[max_points];

    float radius = rand_rangef(DW_MIN_PLANET_RADIUS, DW_MAX_PLANET_RADIUS);

    for(angle = 360.0; angle > 0.0; angle -= 2.0) {
        radius = rand_rangef(DW_MIN_PLANET_RADIUS, DW_MAX_PLANET_RADIUS);

        float radian_angle = deg_to_rad(angle);
        v2_polar(&points[counter], radius, radian_angle);
        ++counter;
    }

    planet->curve = curve_multiquadratic(points, counter);

    int vertice_size = planet->curve->points_length + 1;
    int indices_size = vertice_size * 3;
    unsigned int indices[indices_size];
    int center_index = planet->curve->points_length;
    int i;
    for(i = 0; i < indices_size; i += 3) {
        indices[i + 2] = (i == indices_size - 1) ? 0 : i + 1;
        indices[i + 1] = i;
        indices[i] = center_index;
    }

    vec2 vertices[vertice_size];
    vec2 center = {0, 0};

    array_concat(
        vertices,
        planet->curve->points, sizeof(vec2) * planet->curve->points_length,
        &center, sizeof(vec2));

    planet->mesh = mesh_create(vertices, vertice_size, indices, indices_size);
}
