#ifndef DW_SPRITE_COMPONENT_H
#define DW_SPRITE_COMPONENT_H

typedef struct SpritePool SpritePool;

#include "../config.h"
#include "../sprite.h"
#include "../shader.h"
#include "../entity.h"
#include "../cmp.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    Sprite* sprite;
    GLuint program;
} SpriteComponent;


struct SpritePool {
    SpriteComponent items[MAX_RENDERERS];
    SpriteComponent* allocated;
    SpriteComponent* available;
    unsigned int count;
};


SpritePool* spritepool_create();
void* spritepool_add(SpritePool* pool, Sprite* sprite, GLuint program);
void spritepool_destroy(SpritePool* pool);

void spritecomponent_free_pool(SpriteComponent* item);
void spritecomponent_destroy(SpriteComponent* component);
void spritecomponent_deserialize(Entity* entity, SpritePool* pool, cmp_ctx_t* context);


#endif
