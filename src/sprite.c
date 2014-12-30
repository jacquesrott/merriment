#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "almath.h"
#include "texture.h"
#include "buffer.h"

const int num_vertices = 6;
const vec3 quad_vertices[num_vertices] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 0},
};



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

    sprite->attributes[0].buffer = buffer_create(&vertices, sizeof(vertices));
    sprite->attributes[0].size = 3;
    sprite->attributes[1].buffer = buffer_create(&quad_uv, sizeof(quad_uv));
    sprite->attributes[1].size = 2;

    return sprite;
}


void sprite_draw(Sprite* sprite) {
    glEnableVertexAttribArray(0);
    buffer_bind(sprite->buffer);

    int i;
    for(i = 0; i < NB_VERTEX_ATTRIB; ++i) {
        glEnableVertexAttribArray(i);
        buffer_bind(sprite->attributes[i].buffer);
        glVertexAttribPointer(i, sprite->attributes[i].size, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    for(i = 0; i < NB_VERTEX_ATTRIB; ++i) {
        glDisableVertexAttribArray(i);
    }
}


void sprite_destroy(Sprite* sprite) {
    int i;
    for(i = 0; i < NB_VERTEX_ATTRIB; ++i) {
        buffer_destroy(sprite->attributes[i].buffer);
    }
    free(sprite);
}
