#ifndef DW_SCRIPT_COMPONENT_H
#define DW_SCRIPT_COMPONENT_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct ScriptPool ScriptPool;

#include "../entity.h"
#include "../config.h"
#include "../pool.h"
#include "../cmp.h"


typedef struct {
    PoolItem pool;

    ComponentItem* component;
    const char* path;
    const char* instance;
} ScriptComponent;


struct ScriptPool {
    ScriptComponent items[MAX_SCRIPTS];
    ScriptComponent* allocated;
    ScriptComponent* available;
    unsigned int count;
};


ScriptPool* scriptpool_create();
ScriptComponent* scriptpool_add(ScriptPool* pool, lua_State* L, const char* path);
void scriptpool_destroy(ScriptPool* pool);


void scriptcomponent_free_pool(ScriptComponent* item);
void scriptcomponent_init(ScriptComponent* component, lua_State* L);
void scriptcomponent_update(ScriptComponent* component, lua_State* L);
void scriptcomponent_finish(ScriptComponent* component, lua_State* L);
void scriptcomponent_destroy(ScriptComponent* component);
void scriptcomponent_serialize(ScriptComponent* component, lua_State* L, cmp_ctx_t* context);
void scriptcomponent_deserialize(Entity* entity, ScriptPool* pool, cmp_ctx_t* context);

#endif
