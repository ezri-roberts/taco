#include "taco/window.h"

TcWindow window_new(const char *title, uint32_t width, uint32_t height) {

	TC_INFO("Creating Window.");

	TcWindow window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	return window;
}

void window_set_event_callback(TcWindow *window, EventCallback callback) {
	window->callback = callback;
}

void window_on_update(TcWindow *window) {

}

void window_destroy(TcWindow *window) {

	TC_INFO("Destroyed Window.");
}
