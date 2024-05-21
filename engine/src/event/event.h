#ifndef EVENT_H
#define EVENT_H

#include "shrpch.h"
#include "containers/darray.h"

#define MAX_MESSAGE_CODES 16304

typedef enum {

	EVENT_NONE = 0,
	EVENT_WINDOW_RESIZE, EVENT_WINDOW_FOCUS, EVENT_WINDOW_UNFOCUS,
	EVENT_WINDOW_ICONIFIED, EVENT_WINDOW_MOVE,
	EVENT_KEY_PRESS, EVENT_KEY_RELEASE,
	EVENT_MOUSE_PRESS, EVENT_MOUSE_RELEASE,
	EVENT_MOUSE_MOVE, EVENT_MOUSE_SCROLL,
	EVENT_MOUSE_LEAVE, EVENT_MOUSE_ENTER,
	EVENT_CHAR,
	EVENT_APP_QUIT,
	EVENT_MAX_CODE

} shrevent_code;

typedef enum {

	EVENT_CATEGORY_APPLICATION = BIT(0),
	EVENT_CATEGORY_WINDOW = BIT(1),
	EVENT_CATEGORY_INPUT = BIT(2),
	EVENT_CATEGORY_KEYBOARD = BIT(3),
	EVENT_CATEGORY_MOUSE = BIT(4),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(5)

} shrevent_category;

// Should return true if handled.
typedef bool (*shrevent_callback)(u16 code, void *sender, void *listener, const sapp_event *data);

typedef struct shrevent_registered {

	void *listener;
	shrevent_callback callback;

} shrevent_registered;

typedef struct shrevent_entry {
	shrevent_registered *events;
} shrevent_code_entry;

typedef struct shrevent_system {
	bool initialized;
	// Lookup table for event codes.
	shrevent_code_entry registered[MAX_MESSAGE_CODES];
} shrevent_state;

bool shrevent_initialize();
void shrevent_shutdown();
bool shrevent_register(u16 code, void *listener, shrevent_callback on_event);
bool shrevent_unregister(u16 code, void *listener, shrevent_callback on_event);
bool shrevent_fire(u16 code, void *sender, const sapp_event *data);
bool shrevent_in_category(shrevent_code code, shrevent_category category);
bool shrevent_register_category(u16 category, void *listener, shrevent_callback on_event);
bool shrevent_unregister_category(u16 category, void *listener, shrevent_callback on_event);
bool shrevent_register_multi(u16 events[EVENT_MAX_CODE], void *listener, shrevent_callback on_event);
bool shrevent_unregister_multi(u16 events[EVENT_MAX_CODE], void *listener, shrevent_callback on_event);

#endif // !EVENT_H
