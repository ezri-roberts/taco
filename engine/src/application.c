#include "application.h"

static shrapp app = {};
static bool initialized = false;

void shrapp_initialize() {

	memset(&app, 0, sizeof(shrapp));
	initialized = true;

	SHR_INFO("Initializing engine.");

	if (!shrwindow_initialize("Shraybn", 1280, 720)) {
		SHR_ERROR("Window initialization failed.");
	}

	if (!shrevent_initialize()) {
		SHR_ERROR("Event system initialization failed.");
	}

	if (!shrinput_initialize()) {
		SHR_ERROR("Input system initialization failed.");
	}

	shrevent_register(EVENT_APP_QUIT, 0, shrapp_on_event);
	shrevent_register(EVENT_KEY_PRESS, 0, shrapp_on_key);
	shrevent_register(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	app.layers = darray_create(shrlayer);
	app.scene_list = shrscene_list_new();
	
	app.state = APP_STATE_RUNNING;
	SHR_INFO("App initialized.");
}

void shrapp_shutdown() {

	shrevent_unregister(EVENT_APP_QUIT, 0, shrapp_on_event);
	shrevent_unregister(EVENT_KEY_PRESS, 0, shrapp_on_key);
	shrevent_unregister(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	shrscene_list_destroy(&app.scene_list);
	darray_destroy(app.layers);

	shrevent_shutdown();
	shrinput_shutdown();

	SHR_INFO("Shutdown app.");
	initialized = false;
}

void shrapp_run() {
	if (!initialized) return;

	switch (app.state) {
		case APP_STATE_RUNNING: {

			usize layer_amount = darray_length(app.layers);
			for (usize i = 0; i < layer_amount; i++) {

				shrlayer *layer = &app.layers[i];
				if (layer->on_update) layer->on_update(0);
			}

			shrapp_update();
			shrinput_update();

		} break;

		case APP_STATE_QUIT_REQUESTED:
			sapp_quit(); break;

		default: break;
	}
}

shrapp* shrapp_get() {
	return &app;
}

bool shrapp_check_state(shrapp_state state) {
	return (app.state == state);
}

void shrapp_quit() {
	app.state = APP_STATE_QUIT_REQUESTED;
}

// void shrapp_on_event(shrevent *event, void *data) {
bool shrapp_on_event(u16 code, void *sender, void *listener, const sapp_event *data) {

	shrapp *app = (shrapp*)sapp_userdata();

	switch (code) {
		case EVENT_APP_QUIT: {
			SHR_INFO("WINDOW_CLOSE recieved, shutting down.");
			app->state = APP_STATE_QUIT_REQUESTED;
			return true;
		}
	}

	// Was not handled.
	return false;
}

bool shrapp_on_key(u16 code, void *sender, void *listener, const sapp_event *data) {

	if (code == EVENT_KEY_PRESS) {
		
		u16 key_code = data->key_code;
		if (key_code == KEY_A) {
			SHR_TRACE("A PRESSED!");
		}
	}

	return false;
}

void shrapp_layer_new(void *on_attach, void *on_detach, void *on_update) {

	shrlayer layer;
	layer.on_attach = on_attach;
	layer.on_update = on_update;
	layer.on_detach = on_detach;

	if (layer.on_attach) layer.on_attach(0);
	darray_push(app.layers, layer);
}

void shrapp_set_scene(const char *name) {

	for (usize i = 0; i <= app.scene_list.used; i++) {

		if (app.scene_list.scenes[i]->name == name) {

			SHR_INFO("Set scene to: %s", name);

			app.current_scene = app.scene_list.scenes[i];
			break;
		}
	}
}

// Sokol callback functions.
void sokol_init(void) {

	shrrenderer_init(&app.renderer);
	shrapp_start();
}

void sokol_frame(void) {

	shrapp_run();
	shrrenderer_begin(&app.renderer);
	shrapp_draw();
	shrrenderer_end();
}

void sokol_cleanup(void) {

	shrapp_cleanup();
	shrrenderer_cleanup();
	sg_shutdown();

	SHR_INFO("Terminating Engine.");
}

// Handle the event data sokol gives out.
void sokol_event_callback(const sapp_event *e) {

	// shrevent event;
	shrapp* app = (shrapp*)sapp_userdata();

	switch (e->type) {
		case SAPP_EVENTTYPE_KEY_DOWN:
		case SAPP_EVENTTYPE_KEY_UP: {
			bool pressed = (e->type == SAPP_EVENTTYPE_KEY_DOWN);
			shrinput_process_key(e, pressed);
			break;
		}
		case SAPP_EVENTTYPE_MOUSE_MOVE:
			shrevent_fire(EVENT_MOUSE_MOVE, 0, e); break;
		case SAPP_EVENTTYPE_MOUSE_DOWN:
		case SAPP_EVENTTYPE_MOUSE_UP: {
			bool pressed = (e->type == SAPP_EVENTTYPE_MOUSE_DOWN);
			shrinput_process_button(e, pressed);
			break;
		}
		case SAPP_EVENTTYPE_MOUSE_ENTER:
			shrevent_fire(EVENT_MOUSE_ENTER, 0, e); break;
		case SAPP_EVENTTYPE_MOUSE_LEAVE:
			shrevent_fire(EVENT_MOUSE_LEAVE, 0, e); break;
		case SAPP_EVENTTYPE_MOUSE_SCROLL:
			shrevent_fire(EVENT_MOUSE_SCROLL, 0, e); break;
		case SAPP_EVENTTYPE_QUIT_REQUESTED:
			shrevent_fire(EVENT_APP_QUIT, 0, e); break;
		case SAPP_EVENTTYPE_CHAR:
			shrevent_fire(EVENT_CHAR, 0, e); break;
		default: break;
	}
}

void sokol_log_callback(
        const char* tag,                // always "sapp"
        u32 log_level,             // 0=panic, 1=error, 2=warning, 3=info
        u32 log_item_id,           // SAPP_LOGITEM_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        u32 line_nr,               // line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data) {

	(void)log_level; (void)log_item_id; (void)filename_or_null; (void)user_data;

	switch (log_level) {
		case 0: SHR_FATAL("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 1: SHR_ERROR("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 2: SHR_WARN("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 3: SHR_INFO("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
	}
}
