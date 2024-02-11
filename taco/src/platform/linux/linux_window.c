#include "taco/window.h"

Window window_new(const char *title, uint32_t width, uint32_t height) {

	Window window;
	window.title = title;
	window.width = width;
	window.height = height;

	int success = glfwInit();

	TC_ASSERT(success, "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window.target = glfwCreateWindow(width, height, title, NULL, NULL);

	TC_ASSERT(window.target, "Failed to create GLFW window.");
	// glfwMakeContextCurrent(window->target);

	return window;
}

void window_on_update(Window *window) {

	while (!glfwWindowShouldClose(window->target)) {
	
		glfwSwapBuffers(window->target);
		glfwPollEvents();
	}

	glfwDestroyWindow(window->target);
	glfwTerminate();
}

void window_destroy(Window *window) {

	glfwDestroyWindow(window->target);
	glfwTerminate();
	TC_TRACE("Destroyed window.");
}

bool window_should_close(Window *window) {
	return glfwWindowShouldClose(window->target);
}
