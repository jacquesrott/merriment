#ifndef DW_ENTITY_H
#define DW_ENTITY_H


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef struct Entity Entity;
typedef struct EntityPool EntityPool;

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


struct EntityPool {
    Entity items[MAX_ENTITIES];
    Entity* allocated;
    Entity* available;
    unsigned int count;
};


EntityPool* entitypool_create();
void* entitypool_add(EntityPool* pool);
void entitypool_destroy(EntityPool* pool);
void entity_free_pool(Entity* item);
void entity_destroy(Entity* entity);
void entity_serialize(Entity* entity, Scene* scene, cmp_ctx_t* context);
void entity_deserialize(Entity* entity, Scene* scene, cmp_ctx_t* context);


#endif
