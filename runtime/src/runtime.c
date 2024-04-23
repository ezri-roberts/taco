#include "shraybn.h"

shrlayer *dbui_layer;

void dbui_layer_attach() {

	TC_TRACE("[dbui] Layer Attached.");

}

void dbui_layer_update(void *data) {

	shrapp *app = (shrapp*)data;

	dbui_update(&app->dbui);
}

bool dbui_layer_on_event(const shrevent *event, void *data) {

	shrapp *app = (shrapp*)data;
	// dbui_event(&app->dbui, event);

	return true;
}

void shrapp_init(shrapp *app) {

	dbui_layer = shrlayer_new("dbui_layer");
	dbui_layer->on_attach = dbui_layer_attach;
	dbui_layer->on_update = dbui_layer_update;
	dbui_layer->on_event = dbui_layer_on_event;

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
