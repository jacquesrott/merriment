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
#include "timer.h"


Game* merriment;


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

    merriment = game_create(width, height);

    float near = -1.0,
          far = 1.0,
          left = -width / 2.0,
          right = width / 2.0,
          top = height / 2.0,
          bottom = -height / 2.0;

    mat4 view = m4_ortho3d(far, near, top, bottom, left, right);

    game_init(merriment);

    int zoom = 0;

    while(merriment->run == 0) {
        timer_update(merriment->timer);
        while(SDL_PollEvent(&merriment->event)) {
            switch(merriment->event.type) {
                case SDL_QUIT:
                    merriment->run = 1;
                    break;
                case SDL_KEYUP:
                    switch (merriment->event.key.keysym.sym) {
                        case SDLK_BACKSPACE:
                            game_reload(merriment, "tmp/scene-save.mp");
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    zoom = abs(merriment->event.wheel.y);
                    if(merriment->event.wheel.y < 0) {
                        left *= zoom;
                        right *= zoom;
                        top *= zoom;
                        bottom *= zoom;
                        view = m4_ortho3d(far, near, top, bottom, left, right);
                    } else if(merriment->event.wheel.y > 0) {
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

        while(game_is_synced(merriment)) {
            game_step(merriment);
        }

        ScriptComponent* script = merriment->scene->scripts->allocated;
        while(script) {
            ScriptComponent* next = script->pool.next;
            scriptcomponent_update(script, script->component->entity->L);
            script = next;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SDL_GL_SwapWindow(merriment->window);
    }

    game_destroy(merriment);

    return EXIT_SUCCESS;
}

