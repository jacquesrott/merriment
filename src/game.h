#ifndef DW_GAME_H
#define DW_GAME_H

#include <SDL2/SDL.h>

#include "timer.h"
#include "scene.h"


typedef struct {
    int run;
    Scene* scene;
    SDL_Event event;
    SDL_Window* window;
    SDL_GLContext gl;
    GLuint vao_id;
    Timer* timer;
} Game;


Game* game_create(int width, int height);
void game_destroy(Game* game);

void game_init(Game* game);
int game_is_synced(Game* game);
void game_step(Game* game);
void game_reload(Game* game, const char* tmp_path);

#endif
