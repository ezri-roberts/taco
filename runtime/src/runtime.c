#include "shraybn.h"

static u16 events[] = {
	EVENT_MOUSE_PRESS, EVENT_MOUSE_RELEASE,
	EVENT_MOUSE_MOVE, EVENT_MOUSE_ENTER, EVENT_MOUSE_LEAVE,
	EVENT_MOUSE_SCROLL,
	EVENT_KEY_PRESS, EVENT_KEY_RELEASE, EVENT_CHAR
};

void dbui_layer_attach(void *data) {

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

void shrapp_init(shrapp *app) {

	shrapp_layer_new(
		app,
		dbui_layer_attach,
		NULL,
		dbui_layer_update
	);

	shrevent_register_multi(events, 0, dbui_layer_on_event);
}

void shrapp_update(shrapp *app) {

	(void)app;

	// if (input_pressed(MOUSE_LEFT)) {
	// 	TC_TRACE("Left Mouse!");
	// }
	//
	// if (input_pressed(KEY_A)) {
	// 	TC_TRACE("A!");
	// }

}

void shrapp_draw(shrapp *app) {

	(void)app;
	dbui_render();
}

void shrapp_cleanup(shrapp *app) {

	shrevent_unregister_multi(events, 0, dbui_layer_on_event);
	dbui_cleanup();
	shrapp_destroy(app);
}
