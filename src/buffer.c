#include <stdio.h>
#include "buffer.h"


GLuint buffer_create(const void* values, size_t size) {
    GLuint id;
    glGenBuffers(1, &id);
    buffer_bind(id);
    glBufferData(GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);
    buffer_unbind();

    return id;
}


void buffer_bind(GLuint buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}


void buffer_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void buffer_destroy(GLuint buffer) {
    glDeleteBuffers(1, &buffer);
}
