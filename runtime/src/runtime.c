#include "shraybn.h"

shrlayer *dbui_layer;

void dbui_layer_attach() {

	dbui_init();
	TC_TRACE("[DBUI] Layer Attached.");
}

void dbui_layer_update(void *data) {

	shrapp *app = (shrapp*)data;
	dbui_update();

}

bool dbui_layer_on_event(const shrevent *event, void *data) {

	shrapp *app = (shrapp*)data;
	return dbui_event(event);
}

void shrapp_init(shrapp *app) {

	dbui_layer = shrlayer_new("dbui_layer");
	dbui_layer->on_attach = dbui_layer_attach;
	dbui_layer->on_update = dbui_layer_update;
	dbui_layer->on_event = dbui_layer_on_event;

	shrlayer_stack_push(&app->layer_stack, dbui_layer);

}

void shrapp_update(shrapp *app) {

	if (input_pressed(MOUSE_LEFT)) {
		TC_TRACE("Left Mouse!");
	}

	if (input_pressed(KEY_A)) {
		TC_TRACE("A!");
	}

}

void shrapp_draw(shrapp *app) {

	dbui_render();
}

void shrapp_cleanup(shrapp *app) {

	dbui_cleanup();
	shrapp_destroy(app);
}
