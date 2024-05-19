#ifndef EVENT_H
#define EVENT_H

#include "shrpch.h"
#include "containers/darray.h"

#define MAX_MESSAGE_CODES 16304

typedef enum {

	EVENT_NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_UNFOCUS, WINDOW_ICONIFIED, WINDOW_MOVE,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESS, KEY_RELEASE,
	MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, MOUSE_SCROLL,
	MAX_EVENT_CODE = 0xFF

} shrevent_code;

typedef enum {

	EVENT_CATEGORY_APPLICATION = BIT(0),
	EVENT_CATEGORY_INPUT = BIT(1),
	EVENT_CATEGORY_KEYBOARD = BIT(2),
	EVENT_CATEGORY_MOUSE = BIT(3),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)

} shrevent_category;

typedef struct shrevent {

	const char *name;
	shrevent_code type;
	u16 category;
	bool handled;
	sapp_event data;

} shrevent;

typedef bool (*shrevent_callback)(const shrevent*, void*);
// Should return true if handled.
typedef bool (*shrevent_on)(u16 code, void *sender, void *listener, sapp_event data);

typedef struct shrevent_registered {

	void *listener;
	shrevent_on callback;

} shrevent_registered;

typedef struct shrevent_entry {
	shrevent_registered *events;
} shrevent_code_entry;

typedef struct shrevent_system_state {
	bool initialized;
	// Lookup table for event codes.
	shrevent_code_entry registered[MAX_MESSAGE_CODES];
} shrevent_state;

// Event callback function pointer.

shrevent shrevent_new(const shrevent_code type, const sapp_event *data);
void shrevent_copy_data(shrevent *event, sapp_event *e);
bool shrevent_in_category(const shrevent *event, const shrevent_category category);
bool shrevent_dispatch(shrevent *event, const shrevent_code type, const shrevent_callback callback, void *data);
void shrevent_tostring(char *str, const shrevent *event);

bool shrevent_system_initialize(shrevent_state *state);
void shrevent_system_shutdown(shrevent_state *state);
bool shrevent_register(shrevent_state *state, u16 code, void *listener, shrevent_on on_event);
bool shrevent_unregister(shrevent_state *state, u16 code, void *listener, shrevent_on on_event);
bool shrevent_fire(shrevent_state *state, u16 code, void *sender, sapp_event data);

#endif // !EVENT_H
