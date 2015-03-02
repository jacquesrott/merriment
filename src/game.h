#ifndef DW_GAME_H
#define DW_GAME_H

#include <SDL2/SDL.h>

typedef struct {
    int width;
    int height;
    int run;
    SDL_Event event;
    SDL_Window* window;
    SDL_GLContext gl;
    GLuint vao_id;
} Game;


Game* game_create(int width, int height);
void game_destroy(Game* game);

#endif
