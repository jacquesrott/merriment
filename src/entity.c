#include <assert.h>
#include <stdlib.h>

#include "entity.h"

#include "components/meshcomponent.h"
#include "components/physiccomponent.h"
#include "components/spritecomponent.h"
#include "components/scriptcomponent.h"


Entity* entity_create(
        const PhysicComponent* physic,
        const SpriteComponent* sprite,
        const MeshComponent* mesh) {
    Entity* entity = malloc(sizeof(*entity));
    entity->scripts_count = 0;
    entity->physic = physic;
    entity->mesh = mesh;
    entity->sprite = sprite;
}


void entity_destroy(Entity* entity) {
    if(entity->physic) physiccomponent_destroy(entity->physic);
    if(entity->sprite) spritecomponent_destroy(entity->sprite);
    if(entity->mesh) meshcomponent_destroy(entity->mesh);
    int i;
    for(i = 0 ; i < entity->scripts_count ; ++i) {
        scriptcomponent_destroy(entity->scripts[i]);
    }
    free(entity);
}


void entity_add_script_component(Entity* entity, ScriptComponent* component) {
    assert(entity->scripts_count < MAX_SCRIPT_COMPONENTS);
    
    entity->scripts[entity->scripts_count] = component;
    ++entity->scripts_count;
    component->entity = entity;
}
