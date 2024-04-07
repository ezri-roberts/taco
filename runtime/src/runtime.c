#include "taco.h"

void app_init(App *app) {

}

void app_frame(App *app) {

	if (input_down(MOUSE_LEFT)) {

		TC_TRACE("Left Mouse!");
	}

	if (input_pressed(KEY_A)) {

		TC_TRACE("A!");
	}

}

void app_cleanup(App *app) {

	app_destroy(app);
}
