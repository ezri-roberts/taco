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

void window_destroy(TcWindow *window) {

	TC_INFO("Destroyed Window.");
}
