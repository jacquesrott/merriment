#ifndef DW_ENTITY_H
#define DW_ENTITY_H


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "almath.h"
#include "config.h"
#include "pool.h"

typedef struct {
    Entity* next;
    EntityPool* pool;

    lua_State* L;

    struct {
        void* items[MAX_COMPONENTS];
        unsigned int count;
    } components;
} Entity;


typedef struct {
    Entity items[MAX_ENTITIES];
    Entity* available;
    unsigned int count;
    void (*free_item)(void* item);
} EntityPool;


EntityPool* entitypool_create();
void* entitypool_add(EntityPool* pool);
void entitypool_free(EntityPool* pool, Entity* item);
void entity_destroy(Entity* entity);


#endif
