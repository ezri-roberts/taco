#include "application.h"
#include "packer.h"

App* tc_app_new() {

	const char *backend;
	#if defined(SOKOL_GLES3)
		backend = "GLES3";
	#elif defined(SOKOL_D3D11)
		backend = "D3D11";
	#endif

	TC_INFO("Initializing Engine. (%s Backend.)", backend);
	TC_INFO("Creating App.");

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->scene_list = scene_list_new();
	app->state = APP_RUNNING;

	return app;
}

bool tc_app_check_state(App *app, AppState state) {
	return (app->state == state);
}

void tc_app_quit(App *app) {

	app->state = APP_QUIT;
}

void tc_app_run(App *app) {

	// while (app->state == APP_RUNNING) {
	//
	// 	if (WindowShouldClose()) app->state = APP_QUIT;
	//
	// 	app->fps = GetFPS();
	//
	// 	BeginDrawing();
	// 	ClearBackground((Color){50, 50, 50, 255});
	//
	// 	uint16_t layer_amount = app->layer_stack->used;
	//
	// 	for (int i = 0; i <= layer_amount-1; i++) {
	//
	// 		Layer *layer = app->layer_stack->layers[i];
	// 		if (layer->on_update) layer->on_update(GetFrameTime());
	// 	}
	//
	// 	EndDrawing();
	//
	// 	window_on_update(&app->window);
	// }

}

bool tc_app_on_event(Event *e, void *data) {

	App *app = (App*)data;
	EventCallback callback = NULL;

	switch (e->type) {
		case WINDOW_CLOSE:
			callback = tc_app_on_window_close;
	}

	return event_dispatch(e, e->type, callback, &app->window.data);
}

bool tc_app_on_window_close(Event *e, void *data) {

	TcWindowData *win_data = (TcWindowData*)data;

	return true;
}

void tc_app_set_scene(App *app, const char *name) {

	for (int i = 0; i <= app->scene_list.used; i++) {

		if (app->scene_list.scenes[i]->name == name) {

			TC_INFO("Set scene to: %s", name);

			app->current_scene = app->scene_list.scenes[i];
			app->layer_stack = &app->current_scene->layer_stack;
			break;
		}
	}
}

void tc_app_destroy(App *app) {

	scene_list_destroy(&app->scene_list);
	free(app);
	app = NULL;

	TC_INFO("Destroyed App.");
}

// Sokol callback functions.

void sokol_init(void) {

    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });

}

void sokol_frame(void) {

    sg_begin_pass(&(sg_pass){.action = (sg_pass_action) {
        .colors[0] = { .load_action=SG_LOADACTION_CLEAR, .clear_value={0.0f, 0.0f, 0.0f, 1.0f } }
    }, .swapchain = sglue_swapchain() });
    sg_end_pass();
    sg_commit();
}

void sokol_cleanup(void) {

    sg_shutdown();
	tc_app_cleanup();

	TC_INFO("Terminating Engine.");
}

// Handle the event data sokol gives out.
void sokol_event_callback(const sapp_event *e) {

	Event event;
	event.data = e;

	switch (e->type) {
		default:
			event = event_new(EVENT_NONE);
		case SAPP_EVENTTYPE_KEY_DOWN:
			event = event_new(KEY_PRESS); break;
		case SAPP_EVENTTYPE_KEY_UP:
			event = event_new(KEY_RELEASE); break;
		case SAPP_EVENTTYPE_MOUSE_MOVE:
			event = event_new(MOUSE_MOVE); break;
		case SAPP_EVENTTYPE_MOUSE_SCROLL:
			event = event_new(MOUSE_SCROLL); break;
		case SAPP_EVENTTYPE_MOUSE_DOWN:
			event = event_new(MOUSE_PRESS); break;
		case SAPP_EVENTTYPE_MOUSE_UP:
			event = event_new(MOUSE_RELEASE); break;
		case SAPP_EVENTTYPE_RESIZED:
			event = event_new(WINDOW_RESIZE); break;
		case SAPP_EVENTTYPE_QUIT_REQUESTED:
			event = event_new(WINDOW_CLOSE); break;
		case SAPP_EVENTTYPE_FOCUSED:
			event = event_new(WINDOW_FOCUS); break;
		case SAPP_EVENTTYPE_UNFOCUSED:
			event = event_new(WINDOW_UNFOCUS); break;
	}

	tc_app_on_event(&event, sapp_userdata());
}

void sokol_log_callback(
        const char* tag,                // always "sapp"
        uint32_t log_level,             // 0=panic, 1=error, 2=warning, 3=info
        uint32_t log_item_id,           // SAPP_LOGITEM_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        uint32_t line_nr,               // line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data) {

	switch (log_level) {
		case 0: TC_FATAL("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 1: TC_ERROR("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 2: TC_WARN("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 3: TC_INFO("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
	}
}
