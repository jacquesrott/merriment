#ifndef DW_ENTITY_H
#define DW_ENTITY_H


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct Entity Entity;

#include "almath.h"
#include "component.h"
#include "config.h"
#include "pool.h"
#include "scene.h"
#include "cmp.h"


struct ComponentList {
    ComponentItem* head;
    unsigned int count;
};


struct Entity {
    PoolItem pool;

    lua_State* L;

    ComponentList components;
    char name[32];
};


Pool* entitypool_create();
void* entitypool_add(Pool* pool);
void entity_destroy(Entity* entity);
void entity_serialize(Entity* entity, Scene* scene, cmp_ctx_t* context);
void entity_deserialize(Entity* entity, Scene* scene, cmp_ctx_t* context);


#endif
