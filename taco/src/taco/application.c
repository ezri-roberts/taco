#include "application.h"
#include "events/event.h"
#include "log.h"
#include <stdbool.h>
#include <stdlib.h>

App *tc_app_new() {

	App *app = malloc(sizeof(App));
	return app;
}

void tc_app_run(App *app) {

	KeyEvent key_event = key_event_new();

	if (event_in_category(&key_event.event, EVENT_CATEGORY_INPUT)) {
		TC_TRACE("Key Event: 0x%x", &key_event);
	}

	while (true) {

	}

}
