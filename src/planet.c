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

    float water = rand_rangef(DW_PLANET_MIN_RADIUS, DW_PLANET_MAX_RADIUS),
          min = water - rand_rangef(0, DW_PLANET_RADIUS_DIFF),
          max = water + rand_rangef(0, DW_PLANET_RADIUS_DIFF),
          radius;

    for(angle = max_points; angle > 0.0; angle -= 2.0) {
        radius = rand_rangef(min, max);

        float radian_angle = deg_to_rad(angle);
        v2_polar(&points[counter], radius, radian_angle);
        ++counter;
    }

    planet->curve = curve_multiquadratic(points, counter);

    int vertice_size = planet->curve->points_length + 1;
    int indices_size = planet->curve->points_length * 3;
    unsigned int indices[indices_size];
    int center_index = 0;
    int i;
    for(i = 0; i < planet->curve->points_length; i++) {
        int index = i * 3;
        indices[index] = ((i + 1) == planet->curve->points_length - 1) ? 1 : i + 1;
        indices[index + 1] = i;
        indices[index + 2] = center_index;
    }

    vec2 vertices[vertice_size];
    vec2 center = {0, 0};

    array_concat(
        vertices,
        &center, sizeof(vec2),
        planet->curve->points, sizeof(vec2) * planet->curve->points_length
    );

    planet->mesh = mesh_create(vertices, vertice_size, indices, indices_size);
}
