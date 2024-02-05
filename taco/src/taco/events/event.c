#include "event.h"

bool event_in_category(Event *event, EventCategory category) {
	return event->category & category;
}
