#include <stdlib.h>

#include "sprite.h"


SpritePool* spritepool_create() {
    SpritePool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_SPRITES);
    pool->free = spritepool_free;
    return pool;
}


void* spritepool_add(SpritePool* pool, Entity* entity, Sprite* sprite, GLuint program) {
    SpriteComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpritePool stack overflow.\n", name);
        return NULL;
    }

    item->entity = entity;
    item->sprite = sprite;
    item->program = program;

    return item;
}

void spritepool_free(SpritePool* pool, SpriteComponent* item) {
    spritecomponent_destroy(item);
    pool_set_available(pool, item);
}


void spritecomponent_destroy(SpriteComponent* component) {
    sprite_destroy(component->sprite);
    program_destroy(component->program);
}
