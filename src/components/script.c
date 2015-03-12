#include <stdlib.h>
#include <SDL2/SDL.h>

#include "script.h"


static void pool_init(ScriptPool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.next = NULL;
    pool->count = 0;
}


void scriptpool_destroy(ScriptPool* pool) {
    ScriptComponent* item = pool->allocated;
    while(item) {
        scriptcomponent_free_pool(item);
        item = item->pool.next;
    }
    free(pool);
}


static ScriptComponent* pool_pop_available(ScriptPool* pool) {
    ScriptComponent* item = pool->available;
    pool->available = item->pool.next;

    item->pool.next = pool->allocated;
    pool->allocated = item;
    item->pool.previous = NULL;
    ++pool->count;
    return item;
}


static void pool_set_available(ScriptPool* pool, ScriptComponent* item) {
    ScriptComponent* previous = item->pool.previous;
    ScriptComponent* next = item->pool.next;

    if(next) next->pool.previous = previous;
    if(previous) previous->pool.next = next;

    item->pool.next = pool->available;
    pool->available = item;
    --pool->count;
}


ScriptPool* scriptpool_create() {
    ScriptPool* pool = malloc(sizeof(*pool));
    pool_init(pool, MAX_SCRIPTS);
    return pool;
}


ScriptComponent* scriptpool_add(ScriptPool* pool, lua_State* L, const char* path) {
    ScriptComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ScriptPool stack overflow.\n");
        return NULL;
    }

    item->component = NULL;
    item->path = path;
    int status = luaL_loadfile(L, path);
    status |= lua_pcall(L, 0, 0, 0);
    if(status) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "instance");
    item->instance = lua_tostring(L, -1);
    lua_pop(L, 1);

    return item;
}


void scriptcomponent_free_pool(ScriptComponent* item) {
    pool_set_available(item->pool.container, item);
}


static void script_run_method(lua_State* L, const char* instance, const char* name) {
    lua_getglobal(L, instance);
    lua_getfield(L, -1, name);
    lua_pushvalue(L, -2);

    if(lua_pcall(L, 1, 0, 0)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, "Couldn't run `%s` for %s: %s\n", 
            name, instance, lua_tostring(L, -1));
    }
}


void scriptcomponent_init(ScriptComponent* component, lua_State* L) {
    script_run_method(L, component->instance, "init");
}


void scriptcomponent_update(ScriptComponent* component, lua_State* L) {
    script_run_method(L, component->instance, "update");
}

void scriptcomponent_finish(ScriptComponent* component, lua_State* L) {
    script_run_method(L, component->instance, "finish");
}
