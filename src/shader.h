#ifndef DW_SHADER_H
#define DW_SHADER_H

#include <OpenGL/GL3.h>


GLuint shader_load(const char* path, GLenum type);
GLuint program_load(const char* vertex_path, const char* fragment_path);


#endif
