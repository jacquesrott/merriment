#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include <stdio.h>
#include "game.h"
#include "config.h"
#include "almath.h"
#include "shader.h"
#include "texture.h"
#include "sprite.h"


Game* dwarves;


void quit_dwarves() {
    game_destroy(dwarves);
    SDL_Quit();
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

    float far = 1000.0,
          near = 0.1,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    mat4 view = m4_orthographic(near, far, top, bottom, left, right);
    m4_print(&view);
    GLuint program = program_load("assets/vertex.vs", "assets/fragment.fs");
    GLuint texture = texture_load("assets/red_square.png");
    Sprite* sprite = sprite_create(texture);

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

        program_bind(program);
        texture_bind(texture);

        sprite_draw(sprite);

        texture_unbind();
        program_unbind();

        SDL_GL_SwapWindow(dwarves->window);
    }

    program_destroy(program);
    glDeleteVertexArrays(1, &vao_id);
    texture_destroy(texture);
    sprite_destroy(sprite);

    return EXIT_SUCCESS;
}

