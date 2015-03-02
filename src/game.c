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

    glGenVertexArrays(1, &game->vao_id);
    glBindVertexArray(game->vao_id);
    check_gl_errors("VAO creation");

    return game;
}


void game_destroy(Game* game) {
    glDeleteVertexArrays(1, &game->vao_id);
    glcontext_destroy(game->gl);
    window_destroy(game->window);
    free(game);
    SDL_Quit();
    printf("Quitting Dwarves.\n");
}
