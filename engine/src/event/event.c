#include "event.h"
#include "containers/darray.h"

bool shrevent_system_initialize(shrevent_state *state) {
	if (state->initialized) {
		return false;
	}
	state->initialized = false;
	memset(state, 0, sizeof(shrevent_state));

	state->initialized = true;

	TC_INFO("Event System Initialized.");
	return true;
}

void shrevent_system_shutdown(shrevent_state *state) {

	for (u16 i = 0; i < MAX_MESSAGE_CODES; i++) {
	
		if (state->registered[i].events != 0) {
			darray_destroy(state->registered[i].events);
			state->registered[i].events = 0;
		}
	}
	TC_INFO("Event System Shutdown.");
}

bool shrevent_register(shrevent_state *state, u16 code, void *listener, shrevent_on on_event) {

	if (!state->initialized) return false;

	if (state->registered[code].events == 0) {
		state->registered[code].events = darray_create(shrevent_registered);
	}

	u64 registered_count = darray_length(state->registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {
		if (state->registered[code].events[i].listener == listener) {
			// TODO: Warn.
			return false;
		}
	}

	shrevent_registered event;
	event.listener = listener;
	event.callback = on_event;
	darray_push(state->registered[code].events, event);

	return true;
}

bool shrevent_unregister(shrevent_state *state, u16 code, void *listener, shrevent_on on_event) {

	if (!state->initialized) return false;

	if (state->registered[code].events == 0) {
		// TODO: Warn.
		return false;
	}

	u64 registered_count = darray_length(state->registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {

		shrevent_registered e = state->registered[code].events[i];
		if (e.listener == listener && e.callback == on_event) {
			
			shrevent_registered popped_event;
			darray_pop_at(state->registered[code].events, i, &popped_event);
			return true;
		}
	}

	// Not found.
	return false;
}

bool shrevent_fire(shrevent_state *state, u16 code, void *sender, sapp_event data) {

	if (!state->initialized) return false;

	if (state->registered[code].events == 0) {
		return false;
	}

	u64 registered_count = darray_length(state->registered[code].events);
	for (u64 i = 0; i < registered_count; ++i) {

		shrevent_registered e = state->registered[code].events[i];
		if (e.callback(code, sender, e.listener, data)) {
			// Has been handled. Do not send to other listeners.
			return true;
		}
	}

	// Not found.
	return false;
}

shrevent shrevent_new(const shrevent_code type, const sapp_event *data) {

	shrevent event;
	event.type = type;
	event.data = *data;
	event.handled = false;

	u16 cat_key_input = EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT;
	u16 cat_mouse_input = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT;
	u16 cat_mouse_btn = EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_MOUSE_BUTTON
		| EVENT_CATEGORY_INPUT;

	switch (event.type) {
		case EVENT_NONE: break;
		case KEY_PRESS: 			event.category = cat_key_input; 			 break;
		case KEY_RELEASE: 			event.category = cat_key_input; 			 break;
		case MOUSE_MOVE: 			event.category = EVENT_CATEGORY_MOUSE; 		 break;
		case MOUSE_SCROLL: 			event.category = cat_mouse_input; 			 break;
		case MOUSE_PRESS:  			event.category = cat_mouse_btn; 			 break;
		case MOUSE_RELEASE: 		event.category = cat_mouse_btn; 			 break;
		case WINDOW_RESIZE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_CLOSE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_FOCUS:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_UNFOCUS:		event.category = EVENT_CATEGORY_APPLICATION; break;
		case WINDOW_MOVE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_TICK:				event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_UPDATE:			event.category = EVENT_CATEGORY_APPLICATION; break;
		case APP_RENDER:			event.category = EVENT_CATEGORY_APPLICATION; break;
		default: break;
	}

	return event;
}

void shrevent_tostring(char *str, const shrevent *event) {

	char type[128];

	switch (event->type) {
		case KEY_PRESS: 	 sprintf(type, "Key Press");	  break;
		case KEY_RELEASE: 	 sprintf(type, "Key Release");	  break;
		case MOUSE_MOVE: 	 sprintf(type, "Mouse Move");	  break;
		case MOUSE_SCROLL: 	 sprintf(type, "Mouse Scroll");	  break;
		case MOUSE_PRESS:  	 sprintf(type, "Mouse Press"); 	  break;
		case MOUSE_RELEASE:  sprintf(type, "Mouse Release");  break;
		case WINDOW_RESIZE:	 sprintf(type, "Window Resize");  break;
		case WINDOW_CLOSE:	 sprintf(type, "Window Close");   break;
		case WINDOW_FOCUS:	 sprintf(type, "Window Focus");   break;
		case WINDOW_UNFOCUS: sprintf(type, "Window Unfocus"); break;
		case WINDOW_MOVE:	 sprintf(type, "Window Move"); 	  break;
		case APP_TICK:		 sprintf(type, "App Tick"); 	  break;
		case APP_UPDATE:	 sprintf(type, "App Update"); 	  break;
		case APP_RENDER:	 sprintf(type, "App Render"); 	  break;
		default: break;
	}

	sprintf(str, "%s", type);
}

bool shrevent_in_category(const shrevent *event, const shrevent_category category) {
	return event->category & category;
}

bool shrevent_dispatch(shrevent *event, const shrevent_code type, const shrevent_callback callback, void *data) {

	if (type == event->type && callback != NULL) {

		// Log out event info.
		char event_str[128];
		shrevent_tostring(event_str, event);
		TC_INFO("Dispatch Event '%s'", event_str);

		event->handled = callback(event, data);

		return event->handled;
	}

	return false;
}
