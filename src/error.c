#include "error.h"


void check_gl_errors(const char* message) {
    GLenum errno = glGetError();

    if(errno > 0) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "OpenGL - %s - ERROR: %i\n", message, errno);
    }
}


void print_sdl_error(const char* message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s SDL error=%s\n", message);
    exit(1);
}

