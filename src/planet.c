#include <time.h>
#include <stdlib.h>

#include "planet.h"
#include "random.h"
#include "config.h"


Planet* planet_create() {
    Planet* planet = malloc(sizeof(*planet));
    planet->radius = 0;
    planet->transform = m4_identity();
    planet->mesh = mesh_create();

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
    int size = sizeof(vec2*) * max_points;
    int counter = 0;
    float angle = 360.0;

    vec2** points = malloc(size);

    srandom(time(NULL));

    float radius = rand_rangef(DW_MIN_PLANET_RADIUS, DW_MAX_PLANET_RADIUS);

    while(angle > 0.0) {
        if(counter >= size) {
            size += sizeof(vec2*) * max_points;
            points = realloc(points, size);
        }
        radius = rand_rangef(DW_MIN_PLANET_RADIUS, DW_MAX_PLANET_RADIUS);
        angle -= rand_rangef(1.0, 2.0);

        vec2* point = malloc(sizeof(*point));
        float radian_angle = deg_to_rad(angle);
        v2_polar(point, radius, radian_angle);
        points[counter] = point;
        ++counter;
    }

    counter = round_down(counter, 3);
    planet->curve = curve_multiquadratic(points, counter);

    int indices_size = planet->curve->points_length;
    vec3** indices = malloc(sizeof(vec3) * indices_size);
    int center_index = planet->curve->points_length;
    int i;
    for(i = 0; i < indices_size; ++i) {
        vec3* triangle = malloc(sizeof(*triangle));
        triangle->x = center_index;
        triangle->y = i;
        triangle->z = (i == indices_size - 1) ? 0 : i + 1;
        indices[i] = triangle;
    }

    planet->mesh->buffer = buffer_create(planet->curve->points, planet->curve->points_length);

    free(points);
}
