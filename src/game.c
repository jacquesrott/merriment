#include <time.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include "game.h"
#include "error.h"
#include "window.h"


Game* game_create(int width, int height) {
    srand(time(NULL));

    Game* game = malloc(sizeof(*game));
    game->run = 0;

    game->window = window_create(width, height);
    game->gl = glcontext_create(game->window);
    game->space = cpSpaceNew();
    game->timer = timer_create();

    glGenVertexArrays(1, &game->vao_id);
    glBindVertexArray(game->vao_id);
    check_gl_errors("VAO creation");

    return game;
}


int game_is_synced(Game* game) {
    return game->timer->accumulator >= game->timer->dt;
}


void game_step(Game* game) {
    cpSpaceStep(game->space, game->timer->dt);
    timer_sync(game->timer);
}


void game_destroy(Game* game) {
    glDeleteVertexArrays(1, &game->vao_id);
    glcontext_destroy(game->gl);
    window_destroy(game->window);
    timer_destroy(game->timer);
    cpSpaceFree(game->space);
    free(game);
    SDL_Quit();
    printf("Quitting Dwarves.\n");
}
