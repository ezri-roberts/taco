#ifndef EVENT_H
#define EVENT_H

#include "tcpch.h"

typedef enum {

	EVENT_NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_UNFOCUS, WINDOW_ICONIFIED, WINDOW_MOVE,
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

typedef struct Event {

	const char *name;
	EventType type;
	int category;
	bool handled;
	sapp_event data;

} Event;

// Event callback function pointer.
typedef bool (*EventCallback)(const Event*, void*);

Event event_new(const EventType type, const sapp_event *data);
void event_copy_data(Event *event, sapp_event *e);
bool event_in_category(const Event *e, const EventCategory category);
bool event_dispatch(Event *e, const EventType type, const EventCallback callback, void *data);
void event_tostring(char *str, const Event *e);

#endif // !EVENT_H
