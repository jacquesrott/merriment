#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <OpenGL/gl3.h>

#include "error.h"
#include "texture.h"


void texture_bind(GLuint id) {
    glBindTexture(GL_TEXTURE_2D, id);
}


void texture_unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}


void texture_destroy(GLuint id) {
    glDeleteTextures(1, &id);
}


int texture_get_param(GLuint texture, GLenum param) {
    int value;
    texture_bind(texture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, param, &value);
    texture_unbind();
    return value;
}


GLuint texture_load(const char* path) {
    GLuint id;
    glGenTextures(1, &id);

    SDL_Surface *texture;
    texture = IMG_Load(path);

    if(texture == NULL) {
        return id;
    }

    texture_bind(id);

    glTexImage2D(
        GL_TEXTURE_2D,
        0, GL_RGBA,
        texture->w, texture->h,
        0, GL_BGRA,
        GL_UNSIGNED_BYTE, 
        texture->pixels
    );
    check_gl_errors("texture load 2D data");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    check_gl_errors("texture set parameters");

    glGenerateMipmap(GL_TEXTURE_2D);
    check_gl_errors("texture mipmap generation");

    texture_unbind();
    SDL_FreeSurface(texture);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Texture \"%s\" loaded.\n", path);

    return id;
}
