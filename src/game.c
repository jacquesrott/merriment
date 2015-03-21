#include <time.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <chipmunk/chipmunk.h>

#include "game.h"
#include "error.h"
#include "window.h"
#include "config.h"
#include "scene.h"


Game* game_create(int width, int height) {
    srand(time(NULL));

    Game* game = malloc(sizeof(*game));
    game->run = 0;

    game->window = window_create(width, height);
    game->gl = glcontext_create(game->window);
    game->timer = timer_create();

    glGenVertexArrays(1, &game->vao_id);
    glBindVertexArray(game->vao_id);
    check_gl_errors("VAO creation");

    game->scene = scene_create();

    return game;
}


void game_init(Game* game) {
    scene_deserialize(game->scene, DW_DEFAULT_SCENE);
}


int game_is_synced(Game* game) {
    return game->timer->accumulator >= game->timer->dt;
}


void game_step(Game* game) {
    cpSpaceStep(game->scene->space, game->timer->dt);
    timer_sync(game->timer);
}


void game_destroy(Game* game) {
    if(game->timer) timer_destroy(game->timer);
    if(game->scene) scene_destroy(game->scene);

    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroy Vertex Arrays.\n");
    glDeleteVertexArrays(1, &game->vao_id);
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroy GL context.\n");
    glcontext_destroy(game->gl);

    if(game->window) window_destroy(game->window);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Quitting Galaczy.\n");
    SDL_Quit();
    free(game);
}
