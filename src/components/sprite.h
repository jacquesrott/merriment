#ifndef DW_SPRITE_COMPONENT_H
#define DW_SPRITE_COMPONENT_H


#include "../config.h"
#include "../sprite.h"
#include "../shader.h"
#include "../entity.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    Sprite* sprite;
    GLuint program;
} SpriteComponent;


typedef struct {
    SpriteComponent items[MAX_RENDERERS];
    SpriteComponent* allocated;
    SpriteComponent* available;
    unsigned int count;
} SpritePool;


SpritePool* spritepool_create();
void* spritepool_add(SpritePool* pool, Sprite* sprite, GLuint program);
void spritepool_destroy(SpritePool* pool);

void spritecomponent_free_pool(SpriteComponent* item);
void spritecomponent_destroy(SpriteComponent* component);


#endif
