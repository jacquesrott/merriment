#ifndef DW_WINDOW_H
#define DW_WINDOW_H

#include <SDL2/SDL.h>

SDL_Window* window_create(int width, int heigth);
void window_destroy(SDL_Window* window);

void glcontext_init();
SDL_GLContext* glcontext_create(SDL_Window* window);
void glcontext_destroy(SDL_GLContext* gl);


#endif
