#include "shraybn.h"

void shrapp_init(shrapp *app) {

}

void shrapp_frame(shrapp *app) {

	if (input_pressed(MOUSE_LEFT)) {
		TC_TRACE("Left Mouse!");
	}

	if (input_pressed(KEY_A)) {
		TC_TRACE("A!");
	}

}

void shrapp_cleanup(shrapp *app) {

	shrapp_destroy(app);
}
