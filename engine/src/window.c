#include "window.h"

static shrwindow window = {};
static bool initialized = false;

bool shrwindow_initialize(const char *title, u32 width, u32 height) {
	if (initialized) return false;

	initialized = false;
	memset(&window, 0, sizeof(shrwindow));

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	shrevent_register(EVENT_WINDOW_RESIZE, 0, shrwindow_on_event);

	initialized = true;

	SHR_INFO("Window initialized.");
	return true;
}

void shrwindow_shutdown() {

	shrevent_unregister(EVENT_WINDOW_RESIZE, 0, shrwindow_on_event);

	initialized = false;
	SHR_INFO("Window shutdown.");
}

shrwindow_data* shrwindow_get_data() {
	return &window.data;
}

bool shrwindow_on_event(u16 code, void *sender, void *listener, const sapp_event *data) {

	shrwindow_data *win_data = &window.data;

	switch (code) {
		case EVENT_WINDOW_RESIZE: {
			win_data->width = data->window_width;
			win_data->height = data->window_height;
			return true;
		}
	}

	// Was not handled.
	return false;
}

// bool shrwindow_on_resize(const shrevent *event, void *data) {
//
// 	shrwindow_data *win_data = (shrwindow_data*)data;
//
// 	win_data->width = event->data.window_width;
// 	win_data->height = event->data.window_height;
//
// 	return true;
// }
//
// bool shrwindow_on_focus(const shrevent *event, void *data) {
//
// 	(void)event; (void)data;
//
// 	return true;
// }
//
// bool shrwindow_on_unfocus(const shrevent *event, void *data) {
//
// 	(void)event; (void)data;
//
// 	return true;
// }

