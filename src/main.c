#include <time.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include <stdio.h>
#include "game.h"
#include "config.h"
#include "almath.h"
#include "shader.h"
#include "error.h"
#include "texture.h"
#include "buffer.h"
#include "sprite.h"
#include "planet.h"

#include "entity.h"
#include "components/scriptcomponent.h"


Game* dwarves;


void quit_dwarves() {
    game_destroy(dwarves);
    SDL_Quit();
    printf("Quitting Dwarves.\n");
}


int main() {
    srandom(time(NULL));

    int width = 1440, height = 900;
    unsigned int frame_time, current_time, accumulator = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        print_error("Failed to initialize");
    }
    atexit(quit_dwarves);

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    dwarves = game_create(width, height);

    float near = -1.0,
          far = 1.0,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    check_gl_errors("VAO creation");

    mat4 view = m4_ortho3d(far, near, top, bottom, left, right);
    m4_print(&view);
    GLuint program = program_load("assets/vertex.vs", "assets/fragment.fs");
    Sprite* sprite = sprite_create("assets/red_square.png");

    GLuint umatrix_id = glGetUniformLocation(program, "MVP");
    GLuint utexture_id = glGetUniformLocation(program, "texture_sampler");

    Planet* planet = planet_create();
    planet_generate(planet);

    Entity* entity = entity_create(NULL, NULL, NULL);

    ScriptComponent* script = scriptcomponent_create(entity->L, "assets/scripts/player.lua");
    entity_add_script(entity, script);

    int s;
    for(s = 0 ; s < entity->scripts_count ; ++s) {
        scriptcomponent_init(script, entity->L);
    }

    int ja = 0;
    int zoom = 0;

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
                case SDL_MOUSEBUTTONDOWN:
                    switch (dwarves->event.button.button) {
                        case SDL_BUTTON_LEFT:
                            sprite->transform = m4_identity();
                            break;
                        default:
                            ja++;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (dwarves->event.key.keysym.sym) {
                        case SDLK_SPACE:
                            planet_destroy(planet);
                            planet = planet_create();
                            planet_generate(planet);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    zoom = abs(dwarves->event.wheel.y);
                    if(dwarves->event.wheel.y < 0) {
                        left *= zoom;
                        right *= zoom;
                        top *= zoom;
                        bottom *= zoom;
                        view = m4_ortho3d(far, near, top, bottom, left, right);
                    } else if(dwarves->event.wheel.y > 0) {
                        left /= zoom;
                        right /= zoom;
                        top /= zoom;
                        bottom /= zoom;
                        view = m4_ortho3d(far, near, top, bottom, left, right);
                    }
                    break;
                default:
                    break;
            }
        }

        while(accumulator >= DW_DELTA_TIME) {
            if(ja % 2 == 0) {
                mat4 rot = m4_rotatez(0.2);
                mat4 out;
                m4_x_m4(&out, &rot, &sprite->transform);
                sprite->transform = out;
                ja = 1;
            }
            for(s = 0 ; s < entity->scripts_count ; ++s) {
                scriptcomponent_update(script, entity->L);
            }
            accumulator -= DW_DELTA_TIME;
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        program_bind(program);

        sprite_draw(sprite, &view, umatrix_id, utexture_id);
        mesh_draw(planet->mesh, &view, umatrix_id);

        buffer_unbind();
        texture_unbind();
        program_unbind();

        SDL_GL_SwapWindow(dwarves->window);
    }

    for(s = 0 ; s < entity->scripts_count ; ++s) {
        scriptcomponent_finish(script, entity->L);
    }

    entity_destroy(entity);
    program_destroy(program);
    glDeleteVertexArrays(1, &vao_id);
    sprite_destroy(sprite);
    planet_destroy(planet);

    return EXIT_SUCCESS;
}

