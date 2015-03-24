#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "../entity.h"
#include "../config.h"
#include "../pool.h"
#include "../cmp.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    char path[128];
    const char* instance;
} ScriptComponent;


Pool* scriptpool_create();
ScriptComponent* scriptpool_add(Pool* pool, lua_State* L, const char* path);


void scriptcomponent_destroy(ScriptComponent* item);
void scriptcomponent_init(ScriptComponent* component, lua_State* L);
void scriptcomponent_update(ScriptComponent* component, lua_State* L);
void scriptcomponent_finish(ScriptComponent* component, lua_State* L);
void scriptcomponent_destroy(ScriptComponent* component);
void scriptcomponent_serialize(ScriptComponent* component, lua_State* L, cmp_ctx_t* context);
void scriptcomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context);

#endif
