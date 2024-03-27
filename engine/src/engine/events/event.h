#ifndef EVENT_H
#define EVENT_H

#include "tcpch.h"
#include "engine/keycodes.h"

typedef enum {

	EVENT_NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_UNFOCUS, WINDOW_MOVE,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESS, KEY_RELEASE,
	MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, MOUSE_SCROLL

} EventType;

typedef enum {

	EVENT_CATEGORY_APPLICATION = BIT(0),
	EVENT_CATEGORY_INPUT = BIT(1),
	EVENT_CATEGORY_KEYBOARD = BIT(2),
	EVENT_CATEGORY_MOUSE = BIT(3),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)

} EventCategory;

typedef struct {

	const char *name;
	const sapp_event *data;
	EventType type;
	int category;
	bool handled;

} Event;

// Event callback function pointer.
typedef void (*EventCallback)(Event*);

Event event_new(EventType type);
bool event_in_category(Event *e, EventCategory category);
void event_dispatch(Event *e, EventCallback callback);
void event_tostring(char *str, Event *e);

#endif // !EVENT_H
