#include "shraybn.h"

void dbui_layer_attach(void *data) {

	(void)data;

	dbui_init();
	SHR_TRACE("[DBUI] Layer Attached.");
}

void dbui_layer_update(void *data) {

	(void)data;

	dbui_update();
}

bool dbui_layer_on_event(u16 code, void *sender, void *listener, const sapp_event *data) {

	return dbui_event(data);
}

void shrapp_start() {

	shrapp_layer_new((shrlayer_desc) {
		.on_attach = dbui_layer_attach,
		.on_update = dbui_layer_update
	});

	shrevent_register_category(EVENT_CATEGORY_MOUSE, 0, dbui_layer_on_event);
	shrevent_register_category(EVENT_CATEGORY_KEYBOARD, 0, dbui_layer_on_event);
}

void shrapp_update() {

	// if (input_pressed(MOUSE_LEFT)) {
	// 	TC_TRACE("Left Mouse!");
	// }
	//
	// if (input_pressed(KEY_A)) {
	// 	TC_TRACE("A!");
	// }

}

void shrapp_draw() {

	dbui_render();
}

void shrapp_cleanup() {

	shrevent_unregister_category(EVENT_CATEGORY_MOUSE, 0, dbui_layer_on_event);
	shrevent_unregister_category(EVENT_CATEGORY_KEYBOARD, 0, dbui_layer_on_event);

	dbui_cleanup();
	shrapp_shutdown();
}
