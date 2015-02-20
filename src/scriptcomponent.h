#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct ScriptComponent ScriptComponent;

#include "entity.h"


struct ScriptComponent {
    Entity* entity;
    const char* path;
    struct {
        const char* name;
        const char* metatable;
    } instance;
};

ScriptComponent* scriptcomponent_create(lua_State* L, const char* path);
void scriptcomponent_destroy(ScriptComponent* component);


#endif
