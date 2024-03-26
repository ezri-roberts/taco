#ifndef EVENT_H
#define EVENT_H

#include "tcpch.h"
#include "engine/keycodes.h"

typedef enum {

	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESSED, KEY_RELEASED,
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED

} EventType;

typedef enum {

	EVENT_CATEGORY_APPLICATION = BIT(0),
	EVENT_CATEGORY_INPUT = BIT(1),
	EVENT_CATEGORY_KEYBOARD = BIT(2),
	EVENT_CATEGORY_MOUSE = BIT(3),
	EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)

} EventCategory;

typedef struct {

	const sapp_event event;
	const EventType type;
	const char *name;
	const int category;
	bool handled;

} Event;

// Event callback function pointer.
typedef void (*EventCallback)(Event*);

Event event_new();
bool event_in_category(Event *event, EventCategory category);
bool event_dispatch(Event *event);

#endif // !EVENT_H
