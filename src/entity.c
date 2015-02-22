#include <assert.h>
#include <stdlib.h>

#include "entity.h"


Entity* entity_create(
        TransformCompoment* transform,
        PhysicComponent* physic,
        SpriteComponent* sprite,
        MeshComponent* mesh) {
    Entity* entity = malloc(sizeof(*entity));

    entity->transform = transform;
    entity->scripts_count = 0;
    entity->physic = physic;
    entity->mesh = mesh;
    entity->sprite = sprite;

    entity->L = luaL_newstate();
    luaL_openlibs(entity->L);

    return entity;
}


void entity_destroy(Entity* entity) {
    if(entity->physic) physiccomponent_destroy(entity->physic);
    if(entity->sprite) spritecomponent_destroy(entity->sprite);
    if(entity->mesh) meshcomponent_destroy(entity->mesh);
    int i;
    for(i = 0 ; i < entity->scripts_count ; ++i) {
        scriptcomponent_destroy(entity->scripts[i]);
    }
    lua_close(entity->L);
    free(entity);
}


void entity_add_script(Entity* entity, ScriptComponent* component) {
    assert(entity->scripts_count < MAX_SCRIPT_COMPONENTS);

    entity->scripts[entity->scripts_count] = component;
    ++entity->scripts_count;
    component->entity = entity;
}
