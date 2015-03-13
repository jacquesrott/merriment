#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <chipmunk/chipmunk.h>

#include "game.h"
#include "config.h"
#include "almath.h"
#include "shader.h"
#include "texture.h"
#include "buffer.h"
#include "sprite.h"
#include "planet.h"
#include "timer.h"

#include "entity.h"


Game* galaczy;


int main() {
    int width = 1440, height = 900;

    galaczy = game_create(width, height);

    float near = -1.0,
          far = 1.0,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    mat4 view = m4_ortho3d(far, near, top, bottom, left, right);
    GLuint program = program_load("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");
    Sprite* sprite = sprite_create("assets/sprites/red_square.png");

    GLuint umatrix_id = glGetUniformLocation(program, "MVP");
    GLuint utexture_id = glGetUniformLocation(program, "texture_sampler");

    Planet* planet = planet_create();
    planet_generate(planet, galaczy->space);

    int zoom = 0;

    while(galaczy->run == 0) {
        timer_update(galaczy->timer);
        while(SDL_PollEvent(&galaczy->event)) {
            switch(galaczy->event.type) {
                case SDL_QUIT:
                    galaczy->run = 1;
                    break;
                case SDL_KEYUP:
                    switch (galaczy->event.key.keysym.sym) {
                        case SDLK_SPACE:
                            planet_destroy(planet);
                            planet = planet_create();
                            planet_generate(planet, galaczy->space);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    zoom = abs(galaczy->event.wheel.y);
                    if(galaczy->event.wheel.y < 0) {
                        left *= zoom;
                        right *= zoom;
                        top *= zoom;
                        bottom *= zoom;
                        view = m4_ortho3d(far, near, top, bottom, left, right);
                    } else if(galaczy->event.wheel.y > 0) {
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

        while(game_is_synced(galaczy)) {
            game_step(galaczy);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        program_bind(program);

        sprite_draw(sprite, &view, umatrix_id, utexture_id);
        mesh_draw(planet->mesh, &view, umatrix_id);

        buffer_unbind();
        texture_unbind();
        program_unbind();

        SDL_GL_SwapWindow(galaczy->window);
    }

    program_destroy(program);
    sprite_destroy(sprite);
    planet_destroy(planet);

    game_destroy(galaczy);

    return EXIT_SUCCESS;
}

