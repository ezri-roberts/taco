#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "window.h"

void engine_init() {

    // engine.sprites_len = 0;
    // engine.canvases_len = 0;

    glfwInit();
    window_init(&engine.window, 1280, 720, "Game Window");

    engine.gl_version = gladLoadGL(glfwGetProcAddress);
    if (engine.gl_version == 0) {
        printf("Failed to initialize OpenGL context\n");
        exit(-1);
    }

    printf("Loaded OpenGL %d.%d\n",
           GLAD_VERSION_MAJOR(engine.gl_version),
           GLAD_VERSION_MINOR(engine.gl_version)
    );

    glViewport(0, 0, engine.window.width, engine.window.height);
    printf("Engine initialized.\n") ;
    // engine.fps_limit = 60;
    // engine.delta_time = 0;
    // SetTargetFPS(engine.fps_limit);
}

void engine_update() {

    while (!window_should_close(&engine.window)) {

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(engine.window.target);
    }
}

void engine_cleanup() {

    glfwTerminate();
}
