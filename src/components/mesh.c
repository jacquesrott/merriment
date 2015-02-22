#include <stdlib.h>

#include "meshcomponent.h"


MeshComponent* meshcomponent_create(Mesh* mesh, GLuint program) {
    MeshComponent* mesh_component = malloc(sizeof(*mesh));
    mesh_component->mesh = mesh;
    mesh_component->program = program;

    return mesh_component;
}


void meshcomponent_destroy(MeshComponent* component) {
    mesh_destroy(component->mesh);
    program_destroy(component->program);
    free(component);
}
