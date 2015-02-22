#ifndef DW_SPRITE_COMPONENT_H
#define DW_SPRITE_COMPONENT_H

typedef struct SpriteComponent SpriteComponent;

#include "../sprite.h"
#include "../shader.h"
#include "../entity.h"


struct SpriteComponent {
    Entity* entity;
    Sprite* sprite;
    GLuint program;
};


SpriteComponent* spritecomponent_create(Sprite* sprite, GLuint program);
void spritecomponent_destroy(SpriteComponent* component);


#endif
