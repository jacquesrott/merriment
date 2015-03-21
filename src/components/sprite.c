#include <SDL2/SDL.h>
#include <stdlib.h>

#include "sprite.h"
#include "../shader.h"
#include "../sprite.h"


static void pool_init(SpritePool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    pool->allocated = NULL;
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.container = pool;
        pool->items[i].pool.previous = NULL;
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.container = pool;
    pool->items[capacity].pool.previous = NULL;
    pool->items[capacity].pool.next = NULL;
    pool->count = 0;
}


void spritepool_destroy(SpritePool* pool) {
    SpriteComponent* item = pool->allocated;
    while(item) {
        SpriteComponent* next = item->pool.next;
        spritecomponent_free_pool(item);
        item = next;
    }
    free(pool);
}


static SpriteComponent* pool_pop_available(SpritePool* pool) {
    SpriteComponent* item = pool->available;
    pool->available = item->pool.next;

    item->pool.next = pool->allocated;
    pool->allocated = item;
    item->pool.previous = NULL;
    ++pool->count;
    return item;
}


static void pool_set_available(SpritePool* pool, SpriteComponent* item) {
    SpriteComponent* previous = item->pool.previous;
    SpriteComponent* next = item->pool.next;

    if(pool->allocated == item) pool->allocated = next;
    if(next != NULL) next->pool.previous = previous;
    if(previous != NULL) previous->pool.next = next;

    item->pool.next = pool->available;
    pool->available = item;
    --pool->count;
}


SpritePool* spritepool_create() {
    SpritePool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_RENDERERS);
    return pool;
}


void* spritepool_add(SpritePool* pool, Sprite* sprite, GLuint program) {
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

void spritecomponent_free_pool(SpriteComponent* item) {
    spritecomponent_destroy(item);
    pool_set_available(item->pool.container, item);
}


void spritecomponent_destroy(SpriteComponent* component) {
    sprite_destroy(component->sprite);
    program_destroy(component->program);
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


void spritecomponent_deserialize(Entity* entity, SpritePool* pool, cmp_ctx_t* context) {
    char sprite_path[64];
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
            uint32_t path_len = 65;
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
