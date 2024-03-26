#ifndef WINDOW_H
#define WINDOW_H

#include "tcpch.h"
#include "engine/events/event.h"

typedef struct {

	const char *title;
	uint32_t width;
	uint32_t height;
	uint32_t target_fps;
	bool vsync;

} TcWindowData;

typedef struct {

	void *handle;
	TcWindowData data;

	EventCallback callback;

} TcWindow;

TcWindow window_new(const char *title, uint32_t width, uint32_t height);
void window_destroy(TcWindow *window);
void window_on_update(TcWindow *window);
bool window_should_close(TcWindow *window);
void window_set_event_callback(TcWindow *window, EventCallback callback);

#endif // !WINDOW_H
