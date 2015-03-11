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


struct ComponentList {
    ComponentItem* head;
    unsigned int count;
};


struct Entity {
    PoolItem pool;

    lua_State* L;

    ComponentList components;
};


typedef struct EntityPool EntityPool;


struct EntityPool {
    Entity items[MAX_ENTITIES];
    Entity* available;
    unsigned int count;
};


EntityPool* entitypool_create();
void* entitypool_add(EntityPool* pool);
void entitypool_destroy(EntityPool* pool);
void entity_free_pool(Entity* item);
void entity_destroy(Entity* entity);


#endif
