#include <stdio.h>

#include "error.h"
#include "buffer.h"


GLuint buffer_create(const void* values, size_t size) {
    GLuint id;
    glGenBuffers(1, &id);
    buffer_bind(id);
    glBufferData(GL_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);
    check_gl_errors("bind buffer data");
    buffer_unbind();

    return id;
}


GLuint indexbuffer_create(const void* values, size_t size) {
    GLuint id;
    glGenBuffers(1, &id);
    indexbuffer_bind(id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, values, GL_STATIC_DRAW);
    check_gl_errors("bind index buffer data");
    indexbuffer_unbind();

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


void indexbuffer_bind(GLuint buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}


void indexbuffer_unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
