#include "window.h"

shrwindow shrwindow_new(const char *title, int width, int height) {

	TC_INFO("Creating Window.");

	shrwindow window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	return window;
}

void shrwindow_on_update(shrwindow *window) {

}

bool shrwindow_on_resize(const shrevent *event, void *data) {

	shrwindow_data *win_data = (shrwindow_data*)data;

	win_data->width = event->data.window_width;
	win_data->height = event->data.window_height;

	return true;
}

bool shrwindow_on_focus(const shrevent *event, void *data) {

	shrinput_state *state = (shrinput_state*)data;

	return true;
}

bool shrwindow_on_unfocus(const shrevent *event, void *data) {

	shrinput_state *state = (shrinput_state*)data;

	return true;
}

void shrwindow_destroy(shrwindow *window) {

	TC_INFO("Destroyed Window.");
}
