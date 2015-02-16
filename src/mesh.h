#ifndef DW_MESH_H
#define DW_MESH_H

#include "almath.h"
#include "buffer.h"

#define MESH_VERTEX_ATTRIB_COUNT 1


typedef struct {
    mat4 transform;
    int vertices_count;
    VertexAttrib index;
    VertexAttrib attributes[MESH_VERTEX_ATTRIB_COUNT];
} Mesh;


Mesh* mesh_create();
void mesh_destroy(Mesh* mesh);

void mesh_draw(Mesh* mesh, const mat4* view, GLuint umatrix_id);


#endif
