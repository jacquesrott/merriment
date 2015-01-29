#ifndef DW_MESH_H
#define DW_MESH_H

#include "buffer.h"

typedef struct {
    GLuint buffer;
    GLuint index;
} Mesh;


Mesh* mesh_create();
void mesh_destroy(Mesh* mesh);


#endif
