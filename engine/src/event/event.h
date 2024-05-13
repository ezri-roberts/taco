#ifndef EVENT_H
#define EVENT_H

#include "shrpch.h"

typedef enum {

	EVENT_NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_UNFOCUS, WINDOW_ICONIFIED, WINDOW_MOVE,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESS, KEY_RELEASE,
	MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, MOUSE_SCROLL

} shrevent_type;

typedef enum {

	EVENT_CATEGORY_APPLICATION = BIT(0),
	EVENT_CATEGORY_INPUT = BIT(1),
	EVENT_CATEGORY_KEYBOARD = BIT(2),
	EVENT_CATEGORY_MOUSE = BIT(3),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)

} shrevent_category;

typedef struct event {

	const char *name;
	shrevent_type type;
	int category;
	bool handled;
	sapp_event data;

} shrevent;

// Event callback function pointer.
typedef bool (*shrevent_callback)(const shrevent*, void*);

shrevent shrevent_new(const shrevent_type type, const sapp_event *data);
void shrevent_copy_data(shrevent *event, sapp_event *e);
bool shrevent_in_category(const shrevent *event, const shrevent_category category);
bool shrevent_dispatch(shrevent *event, const shrevent_type type, const shrevent_callback callback, void *data);
void shrevent_tostring(char *str, const shrevent *event);

#endif // !EVENT_H
