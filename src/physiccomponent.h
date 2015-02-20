#ifndef DW_PHYSIC_COMPONENT_H
#define DW_PHYSIC_COMPONENT_H


typedef struct PhysicComponent PhysicComponent;

#include "entity.h"


struct PhysicComponent {
    Entity* entity;
};


PhysicComponent* physiccomponent_create();
void physiccomponent_destroy(PhysicComponent* component);


#endif
