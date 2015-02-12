#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H


typedef struct {
    Entity* entity;
} ScriptComponent;

ScriptComponent* scriptcomponent_create();
void scriptcomponent_destroy(ScriptComponent* component);


#endif
