#ifndef EVENT_H
#define EVENT_H

#include "tcpch.h"
#include "taco/keycodes.h"

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

	sapp_event event;
	EventType type;
	const char *name;
	int category;
	bool handled;

} Event;

typedef struct {

	Event event;
	Keycode keycode;

} KeyEvent;

typedef struct {

	Event event;
	Keycode keycode;
	bool is_repeat;

} KeyPressedEvent;

typedef struct {

	Event event;
	Keycode keycode;

} KeyReleasedEvent;

// Event callback function pointer.
typedef void (*EventCallback)(Event*);

// Common event functions.
bool event_in_category(Event *event, EventCategory category);
bool event_dispatch(Event *event);

KeyEvent key_event_new();
KeyPressedEvent key_pressed_event_new();
KeyReleasedEvent key_released_event_new();

#endif // !EVENT_H
