#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "texture.h"
#include "buffer.h"

const int num_vertices = 6;
const vec3 quad_vertices[num_vertices] = {
    {-0.5, -0.5, 0},
    {-0.5, 0.5, 0},
    {0.5, -0.5, 0},
    {0.5, -0.5, 0},
    {-0.5, 0.5, 0},
    {0.5, 0.5, 0},
};

const vec2 quad_uv[num_vertices] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 0},
    {0, 1},
    {1, 1},
};


Sprite* sprite_create(const char* texture_path) {
    Sprite* sprite = malloc(sizeof(*sprite));
    if(sprite == NULL) {
        perror("Sprite creation");
        return NULL;
    }

    sprite->texture = texture_load(texture_path);
    sprite->width = texture_get_param(sprite->texture, GL_TEXTURE_WIDTH);
    sprite->height = texture_get_param(sprite->texture, GL_TEXTURE_HEIGHT);
    sprite->transform = m4_identity();

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


void sprite_draw(Sprite* sprite, const mat4* view, GLuint umatrix_id, GLuint utexture_id) {
    mat4 mvp;
    m4_x_m4(&mvp, view, &sprite->transform);

    glUniformMatrix4fv(umatrix_id, 1, GL_FALSE, (float*) &mvp);
    texture_bind(sprite->texture);
    glUniform1i(utexture_id, 0);

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
    texture_destroy(sprite->texture);
    int i;
    for(i = 0; i < NB_VERTEX_ATTRIB; ++i) {
        buffer_destroy(sprite->attributes[i].buffer);
    }
    free(sprite);
}
