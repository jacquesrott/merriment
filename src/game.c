#include <time.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include "game.h"
#include "config.h"
#include "error.h"


Game* game_create(int width, int height) {
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        print_sdl_error("Failed to initialize");
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, DW_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, DW_OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DW_DOUBLEBUFFER);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DW_DEPTH_SIZE);

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
        print_sdl_error("Failed to create window");
    }

    game->gl = SDL_GL_CreateContext(game->window);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);

    glClearColor(1, 1, 1, 1);

    SDL_LogInfo(
        SDL_LOG_CATEGORY_RENDER,
        "GL version: %s - GLSL version: %s\n",
        glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGenVertexArrays(1, &game->vao_id);
    glBindVertexArray(game->vao_id);
    check_gl_errors("VAO creation");

    return game;
}


void game_destroy(Game* game) {
    glDeleteVertexArrays(1, &game->vao_id);
    if(game->window) {
        SDL_GL_DeleteContext(game->gl);
        SDL_DestroyWindow(game->window);
    }
    free(game);
    SDL_Quit();
    printf("Quitting Dwarves.\n");
}
