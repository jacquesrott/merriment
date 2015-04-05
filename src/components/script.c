#include <stdlib.h>
#include <SDL2/SDL.h>

#include "script.h"


Pool* scriptpool_create() {
    unsigned int item_size = sizeof(ScriptComponent);
    return pool_create(
        item_size,
        MAX_SCRIPTS,
        (void (*)(void*)) scriptcomponent_destroy);
}


ScriptComponent* scriptpool_add(Pool* pool, lua_State* L, const char* path) {
    ScriptComponent* item = pool_pop_available(pool);
    if(item == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ScriptPool stack overflow.\n");
        return NULL;
    }

    item->component = NULL;

    strcpy(item->path, path);

    int status = luaL_loadfile(L, item->path);
    status |= lua_pcall(L, 0, 0, 0);
    if(status) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load file %s: %s\n", item->path, lua_tostring(L, -1));
    }

    lua_getglobal(L, "instance");
    item->instance = lua_tostring(L, -1);
    lua_pop(L, 1);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Script `%s` loaded.\n", item->path);

    return item;
}


void scriptcomponent_destroy(ScriptComponent* component) {
    pool_set_available(component->pool.container, (PoolObject*) component);
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
    lua_pop(L, 1);
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


void script_serialize(lua_State* L, const char* instance, cmp_ctx_t* context) {
    lua_getglobal(L, instance);
    lua_getglobal(L, "serialize");
    lua_pushvalue(L, -2);

    if(lua_pcall(L, 1, 1, 0)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, "Couldn't run `serialize` instance %s : %s\n",
            instance, lua_tostring(L, -1));
    }
    size_t size = lua_strlen(L, -1);
    char serialized[size];
    memcpy(serialized, lua_tostring(L, -1), size);

    cmp_write_str(context, (char*) serialized, size);
    lua_pop(L, 3);
}


void script_deserialize(lua_State* L, const char* instance, const char* serialized, size_t size) {
    lua_getglobal(L, instance);
    lua_getglobal(L, "deserialize");
    lua_pushvalue(L, -2);
    lua_pushlstring(L, serialized, size);

    if(lua_pcall(L, 2, 0, 0)) {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION, "Couldn't run `deserialize` with instance %s and content `%s` : %s\n",
            instance, serialized, lua_tostring(L, -1));
    }
    lua_pop(L, 2);
}


void scriptcomponent_serialize(ScriptComponent* component, lua_State* L, cmp_ctx_t* context) {
    cmp_write_map(context, 2);

    cmp_write_str(context, "path", 4);
    cmp_write_str(context, component->path, strlen(component->path));

    cmp_write_str(context, "instance", 8);
    script_serialize(L, component->instance, context);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Script `%s` serialized.\n", component->path);
}


void scriptcomponent_deserialize(Entity* entity, Pool* pool, cmp_ctx_t* context) {
    uint32_t path_len = 65;
    char script_path[path_len];
    uint32_t key_count;
    char key[32];
    uint32_t instance_len = 256;
    char compiled_instance[instance_len];
    uint32_t key_len;

    cmp_read_map(context, &key_count);

    int k;
    for(k = 0 ; k < key_count ; ++k) {
        key_len = sizeof(key);
        cmp_read_str(context, key, &key_len);
        key[key_len] = 0;

        if(strcmp("path", key) == 0) {
            cmp_read_str(context, script_path, &path_len);
            script_path[path_len] = 0;
        } else if(strcmp("instance", key) == 0) {
            cmp_read_str(context, compiled_instance, &instance_len);
        }
    }

    ScriptComponent* component = scriptpool_add(pool, entity->L, script_path);
    ComponentItem* item = componentlist_push(&entity->components, component, SCRIPT, entity);
    component->component = item;
    scriptcomponent_init(component, entity->L);
    if(instance_len > 1) {
        script_deserialize(entity->L, component->instance, compiled_instance, instance_len);
    }
}
