#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include <stdio.h>
#include "config.h"


void print_error(const char* message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s SDL error=%s\n", message);
    exit(1);
}


typedef struct {
    int width;
    int height;
    int run;
    SDL_Event event;
    SDL_Window* window;
    SDL_GLContext gl;
    unsigned int last_time;
} Game;


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


Game* dwarves;


void quit_dwarves() {
    if(dwarves->window) {
        SDL_GL_DeleteContext(dwarves->gl);
        SDL_DestroyWindow(dwarves->window);
    }
    SDL_Quit();
    free(dwarves);
    printf("Quitting Dwarves.\n");
}


int main() {
    int width = 1440, height = 900;
    unsigned int frame_time, current_time, accumulator = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        print_error("Failed to initialize");
    }
    atexit(quit_dwarves);

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    dwarves = game_create(width, height);

    while(dwarves->run == 0) {
        current_time = SDL_GetTicks();
        frame_time = current_time - dwarves->last_time;
        dwarves->last_time = current_time;

        accumulator += frame_time;
        while(SDL_PollEvent(&dwarves->event)) {
            switch(dwarves->event.type) {
                case SDL_QUIT:
                    dwarves->run = 1;
                    break;
                default:
                    break;
            }
        }

        while(accumulator >= DW_DELTA_TIME) {
            accumulator -= DW_DELTA_TIME;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SDL_GL_SwapWindow(dwarves->window);
    }

    return EXIT_SUCCESS;
}

