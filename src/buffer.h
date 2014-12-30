#ifndef DW_BUFFER_H
#define DW_BUFFER_H

#include <OpenGL/gl3.h>


GLuint buffer_create(const void* values, size_t size);
void buffer_bind(GLuint buffer);
void buffer_unbind();
void buffer_destroy(GLuint buffer);


#endif
