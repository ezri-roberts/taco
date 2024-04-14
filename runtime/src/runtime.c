#include "shraybn.h"

shrlayer *dbui_layer;

// void dbui_layer_attach() {
//
// 	TC_TRACE("dbui layer attached.");
//
// }
//
// void dbui_layer_update() {
//
// }

void shrapp_init(shrapp *app) {

	dbui_layer = shrlayer_new("dbui_layer");
	// dbui_layer->on_attach = dbui_layer_attach;

	shrlayer_stack_push(&app->layer_stack, dbui_layer);

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
