#ifndef WINDOW_H
#define WINDOW_H

#include "tcpch.h"

typedef struct {

	const char *title;
	uint32_t width;
	uint32_t height;
	uint32_t target_fps;
	bool vsync;

} WindowData;

typedef struct {

	void *handle;
	WindowData data;

	void (*callback)();

} Window;

Window window_new(const char *title, uint32_t width, uint32_t height);
void window_destroy(Window *window);
void window_on_update(Window *window);
bool window_should_close(Window *window);

#endif // !WINDOW_H
