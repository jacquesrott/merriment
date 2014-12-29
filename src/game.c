#include "game.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>


void print_error(const char* message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s SDL error=%s\n", message);
    exit(1);
}


Game* game_create(int width, int height) {
    Game* game = malloc(sizeof(*game));

    game->width = width;
    game->height = height;
    game->run = 0;

    game->window = SDL_CreateWindow(
            "Dwarves",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(game->window == NULL) {
        print_error("Failed to create window");
    }

    game->gl = SDL_GL_CreateContext(game->window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, DW_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, DW_OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DW_DOUBLEBUFFER);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DW_DEPTH_SIZE);

    game->last_time = SDL_GetTicks();

    return game;
}

