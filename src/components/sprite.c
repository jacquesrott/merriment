#include <SDL2/SDL.h>
#include <stdlib.h>

#include "sprite.h"


static void pool_init(SpritePool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.next = NULL;
}


void spritepool_destroy(SpritePool* pool) {
    int i;
    for(i = 0 ; i < pool->count ; ++i) {
        SpriteComponent* item = &pool->items[i];
        SpritePool* pool = item->pool.container;
        pool->free_item(item);
    }
}


static SpriteComponent* pool_pop_available(SpritePool* pool) {
    SpriteComponent* item = pool->available;
    pool->available = item->pool.next;
    return item;
}


static void pool_set_available(SpritePool* pool, SpriteComponent* item) {
    SpriteComponent* available = item;
    item->pool.next = pool->available;
    pool->available = available;
}


SpritePool* spritepool_create() {
    SpritePool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_RENDERERS);
    pool->free_item = spritecomponent_free_pool;
    return pool;
}


void* spritepool_add(SpritePool* pool, Entity* entity, Sprite* sprite, GLuint program) {
    SpriteComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpritePool stack overflow.\n");
        return NULL;
    }

    item->entity = entity;
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
