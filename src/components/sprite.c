#include <stdlib.h>

#include "spritecomponent.h"


SpriteComponent* spritecomponent_create(Sprite* sprite, GLuint program) {
    SpriteComponent* component = malloc(sizeof(*component));
    component->sprite = sprite;
    component->program = program;
    return component;
}


void spritecomponent_destroy(SpriteComponent* component) {
    sprite_destroy(component->sprite);
    program_destroy(component->program);
    free(component);
}
