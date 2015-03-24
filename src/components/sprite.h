#ifndef DW_SPRITE_COMPONENT_H
#define DW_SPRITE_COMPONENT_H

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


Pool* spritepool_create();
void* spritepool_add(Pool* pool, Sprite* sprite, GLuint program);

void spritecomponent_destroy(SpriteComponent* component);
void spritecomponent_serialize(SpriteComponent* component, cmp_ctx_t* context);
void spritecomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context);


#endif
