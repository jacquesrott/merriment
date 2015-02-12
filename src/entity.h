#ifndef DW_ENTITY_H
#define DW_ENTITY_H

#define MAX_SCRIPT_COMPONENTS 24


typedef struct {
    vec2 position;
    quat rotation;
    mat4 transform;
    PhysicComponent* physic;
    SpriteComponent* sprite;
    MeshComponent* mesh;
    ScriptComponent* scripts[MAX_SCRIPT_COMPONENTS];
    unsigned int scripts_count;
} Entity;


Entity* entity_create(
        const PhysicComponent* physic,
        const SpriteComponent* sprite,
        const MeshComponent* mesh);
void entity_destroy(Entity* entity);

void entity_add_component(Entity* entity, void* component);
void entity_remove_component(Entity* entity, void* component);


#endif
