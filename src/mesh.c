#include <stdlib.h>

#include "almath.h"
#include "mesh.h"


Mesh* mesh_create(vec2* vertices, int vertices_count, unsigned int* indices, int indices_count) {
    Mesh* mesh = malloc(sizeof(*mesh));
    mesh->vertices_count = vertices_count;
    mesh->transform = m4_identity();

    mesh->attributes[0].buffer = indexbuffer_create(&indices, sizeof(unsigned int));
    mesh->attributes[0].size = indices_count * sizeof(unsigned int);
    mesh->attributes[1].buffer = buffer_create(&vertices, sizeof(vertices));
    mesh->attributes[1].size = 3;

    return mesh;
}


void mesh_destroy(Mesh* mesh) {
    int i;
    for(i = 0; i < MESH_VERTEX_ATTRIB_COUNT; ++i) {
        buffer_destroy(mesh->attributes[i].buffer);
    }

    free(mesh);
}


void mesh_draw(Mesh* mesh, const mat4* view, GLuint umatrix_id) {
    mat4 mvp;
    m4_x_m4(&mvp, view, &mesh->transform);
    glUniformMatrix4fv(umatrix_id, 1, GL_FALSE, (float*) &mvp);

    int i;
    for(i = 1; i < MESH_VERTEX_ATTRIB_COUNT; ++i) {
        glEnableVertexAttribArray(i);
        buffer_bind(mesh->attributes[i].buffer);
       glVertexAttribPointer(i, mesh->attributes[i].size, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    indexbuffer_bind(mesh->attributes[0].buffer);
    glDrawElements(GL_TRIANGLES, mesh->attributes[0].size, GL_UNSIGNED_SHORT, NULL);

    for(i = 1; i < MESH_VERTEX_ATTRIB_COUNT; ++i) {
        glDisableVertexAttribArray(i);
    }
}
