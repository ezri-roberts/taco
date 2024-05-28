#include "event.h"
#include <SDL2/SDL_video.h>

static shrevent_state state;
static bool initialized;

bool shrevent_initialize() {
	if (initialized) return false;

	initialized = false;
	memset(&state, 0, sizeof(shrevent_state));

	initialized = true;

	SHR_INFO("Event System Initialized.");
	return true;
}

void shrevent_shutdown() {
	if (!initialized) return;

	for (u16 i = 0; i < MAX_MESSAGE_CODES; i++) {
	
		if (state.registered[i].events != 0) {
			darray_destroy(state.registered[i].events);
			state.registered[i].events = 0;
		}
	}

	SHR_INFO("Event system shutdown.");
	initialized = false;
}

bool shrevent_register(u16 code, void *listener, shrevent_callback on_event) {

	if (!initialized) return false;

	if (state.registered[code].events == 0) {
		state.registered[code].events = darray_create(shrevent_registered);
	}

	u64 registered_count = darray_length(state.registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {
		if (state.registered[code].events[i].listener == listener) {
			// TODO: Warn.
			return false;
		}
	}

	shrevent_registered event;
	event.listener = listener;
	event.callback = on_event;
	darray_push(state.registered[code].events, event);

	return true;
}

bool shrevent_unregister(u16 code, void *listener, shrevent_callback on_event) {

	if (!initialized) return false;

	if (state.registered[code].events == 0) {
		// TODO: Warn.
		return false;
	}

	u64 registered_count = darray_length(state.registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {

		shrevent_registered e = state.registered[code].events[i];
		if (e.listener == listener && e.callback == on_event) {
			
			shrevent_registered popped_event;
			darray_pop_at(state.registered[code].events, i, &popped_event);
			return true;
		}
	}

	// Not found.
	return false;
}

bool shrevent_fire(u16 code, void *sender, shrevent_data *data) {

	if (!initialized) return false;

	if (state.registered[code].events == 0) {
		return false;
	}

	u64 registered_count = darray_length(state.registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {

		shrevent_registered e = state.registered[code].events[i];
		if (e.callback(code, sender, e.listener, data)) {
			// Has been handled. Do not send to other listeners.
			return true;
		}
	}

	// Not found.
	return false;
}

bool shrevent_register_multi(u16 *events, void *listener, shrevent_callback on_event) {

	for (u8 i = 0; i <= EVENT_MAX_CODE; i++) {
		bool registered = shrevent_register(events[i], listener, on_event);
		if (!registered) return false;
	}

	return true;
}

bool shrevent_unregister_multi(u16 *events, void *listener, shrevent_callback on_event) {

	for (u8 i = 0; i < EVENT_MAX_CODE; i++) {
		return shrevent_unregister(events[i], listener, on_event);
	}

	return false;
}

void shrevent_poll() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP: {
				bool pressed = (event.type == SDL_KEYDOWN);
				// shrinput_process_key(e, pressed);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP: {
				bool pressed = (event.type == SDL_MOUSEBUTTONDOWN);
				// shrinput_process_button(e, pressed);
				break;
			}
			case SDL_MOUSEMOTION:
				// shrinput_process_mouse_move(e);
			break;
			case SDL_MOUSEWHEEL:
				// shrinput_process_mouse_wheel(e);
			break;
			case SDL_QUIT:
				shrevent_fire(EVENT_APP_QUIT, 0, &event); break;

			case SDL_WINDOWEVENT: {
				if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
					shrevent_fire(EVENT_WINDOW_UNFOCUS, 0, &event);
				} else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
					shrevent_fire(EVENT_WINDOW_FOCUS, 0, &event);
				}
			} break;

			default: break;
		}
	}
}

// bool shrevent_register_category(u16 category, void *listener, shrevent_callback on_event) {
//
// 	for (u8 i = 0; i <= EVENT_MAX_CODE; i++) {
// 		if (shrevent_in_category(i, category)) {
// 			if (!shrevent_register(i, listener, on_event)) return false;
// 		}
// 	}
//
// 	return true;
// }

// bool shrevent_unregister_category(u16 category, void *listener, shrevent_callback on_event) {
//
// 	for (u8 i = 0; i <= EVENT_MAX_CODE; i++) {
// 		if (shrevent_in_category(i, category)) {
// 			if (!shrevent_unregister(i, listener, on_event)) return false;
// 		}
// 	}
//
// 	return true;
// }

// bool shrevent_in_category(shrevent_code code, shrevent_category category) {
//
// 	u16 cat;
//
// 	u16 cat_key_input = EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT;
// 	u16 cat_mouse_input = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT;
//
// 	switch (code) {
// 		case EVENT_WINDOW_RESIZE:
// 		case EVENT_WINDOW_FOCUS:
// 		case EVENT_WINDOW_UNFOCUS:
// 		case EVENT_WINDOW_ICONIFIED:
// 		case EVENT_WINDOW_MOVE:
// 			cat = EVENT_CATEGORY_WINDOW; break;
// 		case EVENT_KEY_PRESS:
// 		case EVENT_KEY_RELEASE:
// 			cat = cat_key_input; break;
// 		case EVENT_MOUSE_PRESS:
// 		case EVENT_MOUSE_RELEASE:
// 		case EVENT_MOUSE_SCROLL:
// 			cat = cat_mouse_input; break;
// 		case EVENT_MOUSE_MOVE:
// 		case EVENT_MOUSE_LEAVE:
// 		case EVENT_MOUSE_ENTER:
// 			cat = EVENT_CATEGORY_MOUSE; break;
// 		case EVENT_CHAR:
// 			cat = cat_key_input; break;
// 		case EVENT_APP_QUIT:
// 			cat = EVENT_CATEGORY_APPLICATION; break;
// 		default: break;
// 	}
//
// 	return (cat & category);
// }

