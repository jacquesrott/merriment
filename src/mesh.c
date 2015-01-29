#include <stdlib.h>

#include "mesh.h"


Mesh* mesh_create() {
    Mesh* mesh = malloc(sizeof(*mesh));
    return mesh;
}


void mesh_destroy(Mesh* mesh) {
    buffer_destroy(mesh->buffer);
    buffer_destroy(mesh->index);
    free(mesh);
}
