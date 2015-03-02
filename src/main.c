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
#include "components/script.h"


Game* dwarves;


int main() {
    cpSpace *space = cpSpaceNew();

    int width = 1440, height = 900;

    dwarves = game_create(width, height);
    Timer* timer = timer_create();

    float near = -1.0,
          far = 1.0,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    mat4 view = m4_ortho3d(far, near, top, bottom, left, right);
    GLuint program = program_load("assets/vertex.vs", "assets/fragment.fs");
    Sprite* sprite = sprite_create("assets/red_square.png");

    GLuint umatrix_id = glGetUniformLocation(program, "MVP");
    GLuint utexture_id = glGetUniformLocation(program, "texture_sampler");

    Planet* planet = planet_create();
    planet_generate(planet, space);

    Entity* entity = entity_create(NULL, NULL, NULL, NULL);

    ScriptComponent* script = scriptcomponent_create(entity->L, "assets/scripts/player.lua");
    entity_add_script(entity, script);

    int s;
    for(s = 0 ; s < entity->scripts_count ; ++s) {
        scriptcomponent_init(script, entity->L);
    }

    int zoom = 0;

    while(dwarves->run == 0) {
        timer_update(timer);
        while(SDL_PollEvent(&dwarves->event)) {
            switch(dwarves->event.type) {
                case SDL_QUIT:
                    dwarves->run = 1;
                    break;
                case SDL_KEYUP:
                    switch (dwarves->event.key.keysym.sym) {
                        case SDLK_SPACE:
                            planet_destroy(planet);
                            planet = planet_create();
                            planet_generate(planet, space);
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

        while(timer->accumulator >= timer->dt) {
            for(s = 0 ; s < entity->scripts_count ; ++s) {
                scriptcomponent_update(script, entity->L);
            }
            cpSpaceStep(space, timer->dt);
            timer_sync(timer);
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
    sprite_destroy(sprite);
    planet_destroy(planet);

    cpSpaceFree(space);

    timer_destroy(timer);
    game_destroy(dwarves);

    return EXIT_SUCCESS;
}

