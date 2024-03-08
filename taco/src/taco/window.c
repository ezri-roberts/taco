#include "taco/window.h"

Window window_new(const char *title, uint32_t width, uint32_t height) {

	TC_TRACE("Creating Window.");

	Window window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(width, height, title);
	SetTargetFPS(window.data.target_fps);
	SetExitKey(KEY_NULL);

	window.handle = GetWindowHandle();

	return window;
}

void window_set_event_callback(Window *window, EventCallback callback) {
	window->callback = callback;
}

void window_on_update(Window *window) {

	if (IsWindowResized()) {

		window->data.width = GetScreenWidth();
		window->data.height = GetScreenHeight();
	}
}

void window_destroy(Window *window) {

	CloseWindow();
	TC_TRACE("Destroyed window.");
}
