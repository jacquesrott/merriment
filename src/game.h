#ifndef DW_GAME_H
#define DW_GAME_H

#include <chipmunk/chipmunk.h>
#include <SDL2/SDL.h>

#include "timer.h"


typedef struct {
    int run;
    SDL_Event event;
    SDL_Window* window;
    SDL_GLContext gl;
    GLuint vao_id;
    cpSpace *space;
    Timer* timer;
} Game;


Game* game_create(int width, int height);
void game_destroy(Game* game);

int game_is_synced(Game* game);
void game_step(Game* game);

#endif
