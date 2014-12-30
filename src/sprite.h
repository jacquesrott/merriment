#ifndef DW_SPRITE_H
#define DW_SPRITE_H

#include <OpenGL/gl3.h>

typedef struct {
    GLuint texture;
    GLuint buffer;
    int width, height;
} Sprite;


Sprite* sprite_create(GLuint texture);
void sprite_draw(Sprite* sprite);
void sprite_destroy(Sprite* sprite);

#endif
