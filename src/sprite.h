#ifndef DW_SPRITE_H
#define DW_SPRITE_H

#include <OpenGL/gl3.h>
#include "almath.h"

#define NB_VERTEX_ATTRIB 2

typedef struct {
    GLuint texture;
    int width, height;
    mat4 transform;
    struct VertexAttrib {
        GLuint buffer;
        int size;
    } attributes[NB_VERTEX_ATTRIB];
} Sprite;


Sprite* sprite_create(const char* texture_path);
void sprite_draw(Sprite* sprite, const mat4* view, GLuint umatrix_id, GLuint utexture_id);
void sprite_destroy(Sprite* sprite);

#endif
