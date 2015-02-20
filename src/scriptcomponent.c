#include <stdlib.h>
#include <SDL2/SDL.h>

#include "scriptcomponent.h"


ScriptComponent* scriptcomponent_create(lua_State* L, const char* path) {
    ScriptComponent* component = malloc(sizeof(*component));
    component->path = path;
    int status = luaL_loadfile(L, path);
    if(status) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "instance");
    lua_getfield(L, -1, "name");
    component->instance.name = lua_tostring(L, -1);

    lua_getfield(L, -1, "metatable");
    component->instance.metatable = lua_tostring(L, -1);

    lua_pop(L, 3);

    return component;
}


void scriptcomponent_destroy(ScriptComponent* component) {
    free(component);
}
