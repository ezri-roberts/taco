#ifndef WINDOW_H
#define WINDOW_H

#include "tcpch.h"
#include "events/event.h"

typedef struct {

	const char *title;
	int width;
	int height;
	int target_fps;
	bool vsync;

} TcWindowData;

typedef struct {

	void *handle;
	TcWindowData data;

	EventCallback callback;

} TcWindow;

TcWindow window_new(const char *title, int width, int height);
void window_destroy(TcWindow *window);
void window_on_update(TcWindow *window);
bool window_should_close(TcWindow *window);
void window_set_event_callback(TcWindow *window, EventCallback callback);

#endif // !WINDOW_H
