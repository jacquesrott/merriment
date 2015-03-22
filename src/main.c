#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <chipmunk/chipmunk.h>

#include "game.h"
#include "config.h"
#include "almath.h"
#include "texture.h"
#include "shader.h"
#include "buffer.h"
#include "planet.h"
#include "timer.h"


Game* galaczy;


void handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(EXIT_FAILURE);
}


int main() {
    signal(SIGSEGV, handler);
    int width = 1440, height = 900;

    galaczy = game_create(width, height);

    float near = -1.0,
          far = 1.0,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    mat4 view = m4_ortho3d(far, near, top, bottom, left, right);

    game_init(galaczy);

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
                        case SDLK_BACKSPACE:
                            game_reload(galaczy, "tmp/scene-save.mp");
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

        ScriptComponent* script = galaczy->scene->scripts->allocated;
        while(script) {
            ScriptComponent* next = script->pool.next;
            scriptcomponent_update(script, script->component->entity->L);
            script = next;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SDL_GL_SwapWindow(galaczy->window);
    }

    game_destroy(galaczy);

    return EXIT_SUCCESS;
}

