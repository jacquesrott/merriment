#ifndef DW_ENTITY_H
#define DW_ENTITY_H


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "almath.h"
#include "config.h"
#include "pool.h"


typedef enum {
    CAMERA      = (1 << 0),
    PHYSIC      = (1 << 1),
    TRANSFORM   = (1 << 2),
    SPRITE      = (1 << 3),
    MESH        = (1 << 4),
    SCRIPT      = (1 << 5)
} ComponentType;


typedef struct {
    void* id;
    ComponentType type;
} ComponentItem;


typedef struct {
    PoolItem pool;

    lua_State* L;

    struct {
        ComponentItem* items[MAX_COMPONENTS];
        unsigned int count;
    } components;
} Entity;


typedef struct EntityPool EntityPool;


struct EntityPool {
    Entity items[MAX_ENTITIES];
    Entity* available;
    unsigned int count;
    void (*free_item)(Entity* item);
};


EntityPool* entitypool_create();
void* entitypool_add(EntityPool* pool);
void entitypool_destroy(EntityPool* pool);
void entity_free_pool(Entity* item);
void entity_destroy(Entity* entity);


#endif
