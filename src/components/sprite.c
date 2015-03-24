#include <SDL2/SDL.h>
#include <stdlib.h>

#include "sprite.h"
#include "../shader.h"
#include "../sprite.h"


Pool* spritepool_create() {
    unsigned int item_size = sizeof(Entity);
    return pool_create(
        item_size,
        MAX_RENDERERS,
        (void (*)(void*)) spritecomponent_destroy);
}


void* spritepool_add(Pool* pool, Sprite* sprite, GLuint program) {
    SpriteComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpritePool stack overflow.\n");
        return NULL;
    }

    item->component = NULL;
    item->sprite = sprite;
    item->program = program;

    return item;
}

void spritecomponent_destroy(SpriteComponent* component) {
    sprite_destroy(component->sprite);
    program_destroy(component->program);
    pool_set_available(component->pool.container, (PoolObject*) component);
}


void spritecomponent_serialize(SpriteComponent* component, cmp_ctx_t* context) {
    cmp_write_map(context, 2);

    cmp_write_str(context, "sprite", 6);
    cmp_write_str(context, component->sprite->path, strlen(component->sprite->path));

    cmp_write_str(context, "program", 7);
    cmp_write_array(context, 2);

    // TODO: unhardcode me
    cmp_write_str(context, "assets/shaders/vertex.vs", 24);
    cmp_write_str(context, "assets/shaders/fragment.fs", 26);
}


static void program_deserialize(cmp_ctx_t* context, GLuint* program) {
    uint32_t size;
    cmp_read_array(context, &size);

    if(size != 2) {
        return;
    }
    char vertex_path[64];
    char fragment_path[64];
    uint32_t path_len = 65;

    cmp_read_str(context, vertex_path, &path_len);
    vertex_path[path_len] = 0;

    path_len = 65;
    cmp_read_str(context, fragment_path, &path_len);
    fragment_path[path_len] = 0;

    *program = program_load(vertex_path, fragment_path);
}


void spritecomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context) {
    uint32_t path_len = 65;
    char sprite_path[path_len];
    GLuint program;
    uint32_t key_count;
    char key[32];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("sprite", key) == 0) {
            cmp_read_str(context, sprite_path, &path_len);
            sprite_path[path_len] = 0;
        } else if (strcmp("program", key) == 0) {
            program_deserialize(context, &program);
        }
    }
    Sprite* sprite = sprite_create(sprite_path);
    SpriteComponent* component = spritepool_add(pool, sprite, program);
    ComponentItem* item = componentlist_push(&entity->components, component, SPRITE, entity);
    component->component = item;
}
