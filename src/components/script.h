#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "../entity.h"
#include "../config.h"
#include "../pool.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    const char* path;
    const char* instance;
} ScriptComponent;


typedef struct {
    ScriptComponent items[MAX_SCRIPTS];
    ScriptComponent* available;
    unsigned int count;
} ScriptPool;


ScriptPool* scriptpool_create();
void* scriptpool_add(ScriptPool* pool, Entity* entity, lua_State* L, const char* path);
void scriptpool_destroy(ScriptPool* pool);


void scriptcomponent_free_pool(ScriptComponent* item);
void scriptcomponent_init(ScriptComponent* component, lua_State* L);
void scriptcomponent_update(ScriptComponent* component, lua_State* L);
void scriptcomponent_finish(ScriptComponent* component, lua_State* L);
void scriptcomponent_destroy(ScriptComponent* component);


#endif
