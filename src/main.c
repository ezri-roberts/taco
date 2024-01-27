// #include <stdio.h>
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_log.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

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

int main(int argc, char *argv[]) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *w = glfwCreateWindow(1280, 720, "Game Window", 0, 0);
    glfwMakeContextCurrent(w);
    glfwSwapInterval(1);
    
    sg_setup(&(sg_desc) {
        .logger.func = slog_func,
    });

    sg_pass_action pass_action = {
        .colors[0] = { 
            .load_action=SG_LOADACTION_CLEAR,
            .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
        }
    };

    while (!glfwWindowShouldClose(w)) {

        int cur_width, cur_height;
        glfwGetFramebufferSize(w, &cur_width, &cur_height);
        sg_begin_default_pass(&pass_action, cur_width, cur_height);
        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(w);
        glfwPollEvents();

    }

    sg_shutdown();
    glfwTerminate();

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

    return 0;
}
