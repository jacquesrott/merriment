#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H

typedef struct ScriptComponent ScriptComponent;

#include "../entity.h"


struct ScriptComponent {
    Entity* entity;
};

ScriptComponent* scriptcomponent_create();
void scriptcomponent_destroy(ScriptComponent* component);


#endif
