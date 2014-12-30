#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "almath.h"
#include "texture.h"

const int num_vertices = 6;
const vec3 quad_vertices[num_vertices] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 0},
};


void buffer_bind(GLuint buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}


void buffer_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void buffer_destroy(GLuint buffer) {
    glDeleteBuffers(1, &buffer);
}


Sprite* sprite_create(GLuint texture) {
    Sprite* sprite = malloc(sizeof(*sprite));
    if(sprite == NULL) {
        perror("Sprite creation");
        return NULL;
    }

    sprite->texture = texture;
    sprite->width = texture_get_param(texture, GL_TEXTURE_WIDTH);
    sprite->height = texture_get_param(texture, GL_TEXTURE_HEIGHT);

    vec3 vertices[num_vertices];
    vec3 scale = {sprite->width, sprite->height, 1};
    int i;
    for(i = 0; i < num_vertices; ++i) {
        v3_scale(&vertices[i], &quad_vertices[i], &scale);
    }
    glGenBuffers(1, &sprite->buffer);
    buffer_bind(sprite->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    buffer_unbind();

    return sprite;
}


void sprite_draw(Sprite* sprite) {
    glEnableVertexAttribArray(0);
    buffer_bind(sprite->buffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    buffer_unbind();
}


void sprite_destroy(Sprite* sprite) {
    buffer_destroy(sprite->buffer);
    free(sprite);
}
