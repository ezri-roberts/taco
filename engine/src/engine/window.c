#include "window.h"

TcWindow window_new(const char *title, int width, int height) {

	TC_INFO("Creating Window.");

	TcWindow window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	return window;
}

void window_on_update(TcWindow *window) {

}

bool window_on_resize(const Event *e, void *data) {

	TcWindowData *win_data = (TcWindowData*)data;

	win_data->width = e->data.window_width;
	win_data->height = e->data.window_height;

	return true;
}

void window_destroy(TcWindow *window) {

	TC_INFO("Destroyed Window.");
}
