#include <stdlib.h>
#include <SDL2/SDL.h>

#include "scriptcomponent.h"


ScriptComponent* scriptcomponent_create(lua_State* L, const char* path) {
    ScriptComponent* component = malloc(sizeof(*component));
    component->path = path;
    int status = luaL_loadfile(L, path);
    status |= lua_pcall(L, 0, 0, 0);
    if(status) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "instance");
    component->instance = lua_tostring(L, -1);
    lua_pop(L, 1);

    return component;
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


void scriptcomponent_destroy(ScriptComponent* component) {
    free(component);
}
