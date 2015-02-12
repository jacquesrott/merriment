#ifndef DW_SPRITE_COMPONENT_H
#define DW_SPRITE_COMPONENT_H

#include "../entity.h"
#include "../sprite.h"
#include "../shader.h"

typedef struct {
    Entity* entity;
    Sprite* sprite;
    GLuint program;
} SpriteComponent;


SpriteComponent* spritecomponent_create(const Sprite* sprite, GLuint program);
void spritecomponent_destroy(SpriteComponent* component);


#endif
