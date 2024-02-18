#ifndef WINDOW_H
#define WINDOW_H

#include "tcpch.h"

// typedef void WindowTarget;
#if defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_WINDOWS)
	#define GLFW_INCLUDE_NONE
	#include "GLFW/glfw3.h"
	typedef GLFWwindow WindowTarget;
#endif

typedef struct {

	const char *title;
	uint32_t width;
	uint32_t height;
	bool vsync;

} WindowData;

typedef struct {

	WindowTarget *target;
	WindowData data;

	void (*callback)();

} Window;

Window window_new(const char *title, uint32_t width, uint32_t height);
void window_destroy(Window *window);
void window_on_update(Window *window);
bool window_should_close(Window *window);

#endif // !WINDOW_H
