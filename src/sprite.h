#ifndef DW_SPRITE_H
#define DW_SPRITE_H

#include <OpenGL/gl3.h>

#define NB_VERTEX_ATTRIB 2

typedef struct {
    GLuint texture;
    int width, height;
    struct VertexAttrib {
        GLuint buffer;
        int size;
    } attributes[NB_VERTEX_ATTRIB];
} Sprite;


Sprite* sprite_create(GLuint texture);
void sprite_draw(Sprite* sprite);
void sprite_destroy(Sprite* sprite);

#endif
