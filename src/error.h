#ifndef DW_ERROR_H
#define DW_ERROR_H

#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>


void check_gl_errors(const char* message);
void print_sdl_error(const char* message);

#endif
