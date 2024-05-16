#ifndef WINDOW_H
#define WINDOW_H

#include "shrpch.h"
#include "event/event.h"
#include "input.h"

typedef struct {

	const char *title;
	u32 width;
	u32 height;
	u32 target_fps;
	bool vsync;

} shrwindow_data;

typedef struct {

	void *handle;
	shrwindow_data data;

} shrwindow;

shrwindow shrwindow_new(const char *title, u32 width, u32 height);
void shrwindow_destroy(shrwindow *window);
void shrwindow_on_update(shrwindow *window);
bool shrwindow_should_close(shrwindow *window);

// Event callbacks.
bool shrwindow_on_resize(const shrevent *event, void *data);
bool shrwindow_on_focus(const shrevent *event, void *data);
bool shrwindow_on_unfocus(const shrevent *event, void *data);

#endif // !WINDOW_H
