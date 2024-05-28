#include "window.h"

static shrwindow window = {};
static bool initialized = false;

bool shrwindow_initialize(const char *title, u32 width, u32 height) {
	if (initialized) return false;

	initialized = false;
	memset(&window, 0, sizeof(shrwindow));

	window.data.width = width;
	window.data.height = height;
	window.data.title = title;

	u16 flag;

	#if defined(SHR_GLCORE)
		flag = SDL_WINDOW_OPENGL;
	#endif

	window.target = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		flag
	);

	if (!window.target) {
		return false;
	}

	SDL_GL_CreateContext(window.target);

	initialized = true;

	SHR_INFO("Window initialized.");
	return true;
}

void shrwindow_shutdown() {

	initialized = false;
	SHR_INFO("Window shutdown.");
}

void shrwindow_get_data(shrwindow_data *data) {
	*data = window.data;
}

// void shrwindow_process_resize(const sapp_event *data) {
//
// 	window.data.width = data->window_width;
// 	window.data.height = data->window_height;
//
// 	shrevent_fire(EVENT_WINDOW_RESIZE, 0, data);
// }
//
