#include <stdlib.h>
#include <SDL2/SDL.h>

#include "script.h"


static void pool_init(ScriptPool* pool, unsigned int capacity) {
    pool->available = &pool->items[0];
    pool->allocated = NULL;
    capacity = capacity - 1;
    int i;
    for(i = 0 ; i < capacity ; ++i) {
        pool->items[i].pool.container = pool;
        pool->items[i].pool.previous = NULL;
        pool->items[i].pool.next = &pool->items[i + 1];
    }
    pool->items[capacity].pool.container = pool;
    pool->items[capacity].pool.previous = NULL;
    pool->items[capacity].pool.next = NULL;
    pool->count = 0;
}


void scriptpool_destroy(ScriptPool* pool) {
    ScriptComponent* item = pool->allocated;
    while(item) {
        ScriptComponent* next = item->pool.next;
        scriptcomponent_free_pool(item);
        item = next;
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

    if(next != NULL) next->pool.previous = previous;
    if(previous != NULL) previous->pool.next = next;

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

void script_serialize(lua_State* L, const char* instance, const char* serialized, unsigned int* size) {
    lua_getglobal(L, instance);
    lua_getglobal(L, "serialize");
    lua_pushvalue(L, -2);

    if(lua_pcall(L, 1, 1, 0)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, "Couldn't run `deserialize` with instance %s and content `%s` : %s\n",
            instance, serialized, lua_tostring(L, -1));
    }
    serialized = lua_tostring(L, -1);
    *size = lua_strlen(L, -1);
    lua_pop(L, 1);
}


void script_deserialize(lua_State* L, const char* instance, const char* serialized) {
    lua_getglobal(L, instance);
    lua_getglobal(L, "deserialize");
    lua_pushvalue(L, -2);
    lua_pushstring(L, serialized);

    if(lua_pcall(L, 2, 0, 0)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, "Couldn't run `deserialize` with instance %s and content `%s` : %s\n",
            instance, serialized, lua_tostring(L, -1));
    }
}


void scriptcomponent_serialize(ScriptComponent* component, lua_State* L, cmp_ctx_t* context) {
    cmp_write_map(context, 2);

    cmp_write_str(context, "path", 4);
    cmp_write_str(context, component->path, strlen(component->path));

    cmp_write_str(context, "instance", 4);
    char serialized[128];
    unsigned int size;
    script_serialize(L, component->instance, serialized, &size);
    cmp_write_bin(context, serialized, size);
}


void scriptcomponent_deserialize(Entity* entity, ScriptPool* pool, cmp_ctx_t* context) {
    char script_path[64];
    uint32_t key_count;
    char key[32];
    uint32_t instance_len = 128;
    char compiled_instance[instance_len];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("path", key) == 0) {
            uint32_t path_len = 65;
            cmp_read_str(context, script_path, &path_len);
            script_path[path_len] = 0;
        } else if(strcmp("instance", key) == 0) {
            cmp_read_bin(context, compiled_instance, &instance_len);
            printf("compiled_instance %s - size %d\n", compiled_instance, instance_len);
        }
    }

    ScriptComponent* component = scriptpool_add(pool, entity->L, script_path);
    ComponentItem* item = componentlist_push(&entity->components, component, SCRIPT, entity);
    component->component = item;
    script_deserialize(entity->L, component->instance, compiled_instance);
}
