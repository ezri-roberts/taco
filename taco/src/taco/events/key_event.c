#include "tcpch.h"
#include "event.h"

KeyEvent key_event_new() {

	KeyEvent key_event;

	key_event.event.category = EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT;

	return key_event;
}
