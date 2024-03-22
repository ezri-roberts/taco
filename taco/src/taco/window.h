#ifndef WINDOW_H
#define WINDOW_H

#include "tcpch.h"
#include "taco/events/event.h"

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

	EventCallback callback;

} Window;

Window window_new(const char *title, uint32_t width, uint32_t height);
void window_destroy(Window *window);
void window_on_update(Window *window);
bool window_should_close(Window *window);
void window_set_event_callback(Window *window, EventCallback callback);

#endif // !WINDOW_H
