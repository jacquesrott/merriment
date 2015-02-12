#ifndef DW_MESH_COMPONENT_H
#define DW_MESH_COMPONENT_H

#include "../mesh.h"


typedef struct {
    Entity* entity;
    Mesh* mesh;
    GLuint program;
} MeshComponent;


MeshComponent* meshcomponent_create();
void meshcomponent_destroy(MeshComponent* component);


#endif
