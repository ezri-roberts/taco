#include "window.h"

shrwindow shrwindow_new(const char *title, u32 width, u32 height) {

	TC_INFO("Creating Window.");

	shrwindow window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	return window;
}

bool shrwindow_on_resize(const shrevent *event, void *data) {

	shrwindow_data *win_data = (shrwindow_data*)data;

	win_data->width = event->data.window_width;
	win_data->height = event->data.window_height;

	return true;
}

bool shrwindow_on_focus(const shrevent *event, void *data) {

	(void)event; (void)data;

	return true;
}

bool shrwindow_on_unfocus(const shrevent *event, void *data) {

	(void)event; (void)data;

	return true;
}

void shrwindow_destroy(shrwindow *window) {

	(void)window;
	TC_INFO("Destroyed Window.");
}
