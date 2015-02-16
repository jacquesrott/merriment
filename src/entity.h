#ifndef DW_ENTITY_H
#define DW_ENTITY_H

#define MAX_SCRIPT_COMPONENTS 24

#include "almath.h"

typedef struct Entity Entity;

#include "components/meshcomponent.h"
#include "components/physiccomponent.h"
#include "components/spritecomponent.h"
#include "components/scriptcomponent.h"


struct Entity {
    vec2 position;
    float angle;
    mat4 transform;
    PhysicComponent* physic;
    SpriteComponent* sprite;
    MeshComponent* mesh;
    ScriptComponent* scripts[MAX_SCRIPT_COMPONENTS];
    unsigned int scripts_count;
};


Entity* entity_create(
        PhysicComponent* physic,
        SpriteComponent* sprite,
        MeshComponent* mesh);
void entity_destroy(Entity* entity);

void entity_add_script(Entity* entity, ScriptComponent* component);


#endif
