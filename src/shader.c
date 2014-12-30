#include <errno.h>
#include <OpenGL/GL3.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader.h"


long get_file_size(FILE *file) {
    long file_size;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
}


GLuint shader_load(const char* path, GLenum type) {
    GLuint id = glCreateShader(type);

    FILE* file = fopen(path, "r");
    if(file == NULL) {
        printf("Failed to open %s. ERROR: %d\n", path, errno);
        return -1;
    }

    long file_size = get_file_size(file);
    GLchar* content = calloc(file_size, 1);
    fread(content, file_size - 1, 1, file);
    fclose(file);

    GLint result = GL_FALSE;
    int log_length;

    glShaderSource(id, 1, (const GLchar **) &content, NULL);
    glCompileShader(id);

    free(content);

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
        char shader_error[log_length];
        glGetShaderInfoLog(id, log_length, NULL, (GLchar*) &shader_error);
        printf("\"%s\" - %s\n", path, shader_error);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Shader \"%s\" loaded.\n", path);

    return id;
}


GLuint program_load(const char* vertex_path, const char* fragment_path) {
    GLuint vertex_shader = shader_load(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment_shader = shader_load(fragment_path, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint result = GL_FALSE;
    int log_length;

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if(result == GL_FALSE) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        char program_error[log_length];
        glGetProgramInfoLog(program, log_length, NULL, (GLchar*) &program_error);
        printf("%s\n", program_error);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}


void program_bind(GLuint id) {
    glUseProgram(id);
}


void program_unbind() {
    glUseProgram(0);
}


void program_destroy(GLuint id) {
    glDeleteProgram(id);
}
