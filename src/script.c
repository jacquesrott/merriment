#include <stdio.h>

#include "script.h"

static lua_State* L;


void script_create() {
    L = luaL_newstate();
    luaL_openlibs(L);
}


void script_destroy() {
    lua_close(L);
}
