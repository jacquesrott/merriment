#ifndef DW_MESH_COMPONENT_H
#define DW_MESH_COMPONENT_H

typedef struct MeshComponent MeshComponent;

#include "mesh.h"
#include "entity.h"
#include "shader.h"


struct MeshComponent {
    Entity* entity;
    Mesh* mesh;
    GLuint program;
};


MeshComponent* meshcomponent_create(Mesh* mesh, GLuint program);
void meshcomponent_destroy(MeshComponent* component);


#endif
