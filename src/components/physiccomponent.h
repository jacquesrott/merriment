#ifndef DW_PHYSIC_COMPONENT_H
#define DW_PHYSIC_COMPONENT_H

typedef struct {
    Entity* entity;
} PhysicComponent;


PhysicComponent* physiccomponent_create();
void physiccomponent_destroy(PhysicComponent* component);


#endif
