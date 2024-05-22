#ifndef WINDOW_H
#define WINDOW_H

#include "shrpch.h"
#include "event/event.h"
#include "input.h"

typedef struct shrwindow_data {

	const char *title;
	u32 width;
	u32 height;
	u32 target_fps;
	bool vsync;
} shrwindow_data;

typedef struct {
	shrwindow_data data;
} shrwindow;

bool shrwindow_initialize(const char *title, u32 width, u32 height);
void shrwindow_shutdown();

shrwindow_data* shrwindow_get_data();

// Event callbacks.
// bool shrwindow_on_resize(const shrevent *event, void *data);
// bool shrwindow_on_focus(const shrevent *event, void *data);
// bool shrwindow_on_unfocus(const shrevent *event, void *data);

#endif // !WINDOW_H
