#include "taco/log.h"
#include "taco/window.h"

Window window_new(const char *title, uint32_t width, uint32_t height) {

	TC_TRACE("Creating Window.");

	Window window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;

	int success = glfwInit();

	TC_ASSERT(success, "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window.target = glfwCreateWindow(width, height, title, NULL, NULL);

	TC_ASSERT(window.target, "Failed to create GLFW window.");

	glfwMakeContextCurrent(window.target);
	glfwSetWindowUserPointer(window.target, &window.data);


	return window;
}

void window_on_update(Window *window) {

	while (!glfwWindowShouldClose(window->target)) {
	
		glfwPollEvents();
		glfwSwapBuffers(window->target);
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
