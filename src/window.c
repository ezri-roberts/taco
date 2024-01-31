#include <stdio.h>
#include <stdlib.h>
#include "window.h"

void window_init(Window *window, uint16_t width, uint16_t height, char *title) {

    window->width = width;
    window->height = height;
    window->title = title;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window->target = glfwCreateWindow(
        width, height,
        title,
        NULL, NULL
    );
    glfwMakeContextCurrent(window->target);

    if (window->target == NULL) {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(-1);
    } else {
        printf("Created GLFW window.\n");
    }

}

bool window_should_close(Window *window) {
    return glfwWindowShouldClose(window->target);
}
