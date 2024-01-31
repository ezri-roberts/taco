// #include <stdio.h>
#include "engine.h"

// #include "lua/lua.h"
// #include "lua/lualib.h"
// #include "lua/lauxlib.h"

// int set_size(lua_State *L) {
//
//     int a = luaL_checkinteger(L, 1);
//     int b = luaL_checkinteger(L, 2);
//
//     return 0;
// }
//

Engine engine;

int main(int argc, char *argv[]) {

    engine_init();

    engine_update();
    engine_cleanup();

    return 0;
}

    // lua_State *L = luaL_newstate();
    // luaL_openlibs(L);
    //
    // luaL_Reg EngineLib[] = {
    //     { "set_size", set_size },
    //     { NULL, NULL},
    // };
    //
    // lua_newtable(L);
    // luaL_setfuncs(L, EngineLib, 0);
    // lua_setglobal(L, "Engine");
    //
    // char *code = "Engine.set_size(1280, 720)";
    // // char *code = "print('Lua!!')";
    //
    // if (luaL_dostring(L, code) == LUA_OK) {
    //     lua_pop(L, lua_gettop(L));
    // }
    //
    // lua_close(L);
