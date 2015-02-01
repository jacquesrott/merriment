#ifndef DW_MESH_H
#define DW_MESH_H

#include "buffer.h"

#define MESH_VERTEX_ATTRIB_COUNT 2


typedef struct {
    mat4 transform;
    int vertices_count;
    VertexAttrib attributes[MESH_VERTEX_ATTRIB_COUNT];
} Mesh;


Mesh* mesh_create();
void mesh_destroy(Mesh* mesh);

void mesh_draw(Mesh* mesh, const mat4* view, GLuint umatrix_id);


#endif
