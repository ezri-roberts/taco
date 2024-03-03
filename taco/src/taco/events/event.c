#include "tcpch.h"
#include "event.h"

bool event_in_category(Event *event, EventCategory category) {
	return event->category & category;
}

bool event_dispatch(Event *event) {

	event->handled = true;
	return true;

	// Dispatch event?
}
