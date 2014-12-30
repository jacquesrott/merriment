#ifndef DW_TEXTURE_H
#define DW_TEXTURE_H

#include <OpenGL/gl3.h>

GLuint texture_load(const char* path);
void texture_bind(GLuint id);
void texture_unbind();
void texture_destroy(GLuint id);

#endif
