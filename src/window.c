#include "window.h"
#include "error.h"
#include "config.h"


SDL_Window* window_create(int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        print_sdl_error("Failed to initialize");
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    glcontext_init();

    SDL_Window* window = SDL_CreateWindow(
            "Dwarves",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(window == NULL) {
        print_sdl_error("Failed to create window");
    }

    return window;
}


void window_destroy(SDL_Window* window) {
    SDL_DestroyWindow(window);
}


void glcontext_init() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, DW_OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, DW_OPENGL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, DW_DOUBLEBUFFER);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DW_DEPTH_SIZE);
}


SDL_GLContext* glcontext_create(SDL_Window* window) {
    SDL_GLContext* gl = SDL_GL_CreateContext(window);
    check_gl_errors("GL Context creation");
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

    return gl;
}


void glcontext_destroy(SDL_GLContext* gl) {
    SDL_GL_DeleteContext(gl);
}
