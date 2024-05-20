#include "application.h"

shrapp* shrapp_new() {

	TC_INFO("Initializing Engine.");
	TC_INFO("Creating App.");

	shrapp *app = malloc(sizeof(shrapp));

	app->window = shrwindow_new("Game Window", 1280, 720);

	if (!shrevent_initialize()) {
		TC_ERROR("Event system initialization failed.");
	}

	shrinput_initialize();

	shrevent_register(EVENT_APP_QUIT, 0, shrapp_on_event);
	shrevent_register(EVENT_KEY_PRESS, 0, shrapp_on_key);
	shrevent_register(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	app->layers = darray_create(shrlayer);

	app->scene_list = shrscene_list_new();
	// app->layer_stack = shrlayer_stack_new();
	// app->overlay_stack = shrlayer_stack_new();
	app->state = APP_STATE_RUNNING;

	return app;
}

bool shrapp_check_state(shrapp *app, shrapp_state state) {
	return (app->state == state);
}

void shrapp_quit(shrapp *app) {
	app->state = APP_STATE_QUIT_REQUESTED;
}

void shrapp_run(void *data) {

	shrapp *app = (shrapp*)data;

	if (app->state == APP_STATE_QUIT_REQUESTED) {
		sapp_quit();
	}

	// usize layer_amount = shrlayer_stack_size(&app->layer_stack);
	//
	// for (usize i = 0; i <= layer_amount-1; i++) {
	//
	// 	shrlayer *layer = shrlayer_stack_get(&app->layer_stack, i);
	// 	if (layer->on_update) layer->on_update(app);
	// }

	shrapp_update(app);
	shrinput_update();
}

// void shrapp_on_event(shrevent *event, void *data) {
bool shrapp_on_event(u16 code, void *sender, void *listener, const sapp_event *data) {

	shrapp *app = (shrapp*)sapp_userdata();

	switch (code) {
		case EVENT_APP_QUIT: {
			TC_INFO("WINDOW_CLOSE recieved, shutting down.");
			app->state = APP_STATE_QUIT_REQUESTED;
			return true;
		}
	}

	// Was not handled.
	return false;
	// shrevent_callback callback = NULL;
	// void *pass_data = data;

	// switch (event->type) {
	// 	case WINDOW_CLOSE:
	// 		callback = shrapp_on_quit;
	// 		break;
	// 	case WINDOW_RESIZE:
	// 		callback = shrwindow_on_resize;
	// 		pass_data = &app->window.data;
	// 		break;
	// 	case KEY_PRESS:
	// 		callback = shrapp_on_key;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	case KEY_RELEASE:
	// 		callback = shrapp_on_key;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	case MOUSE_PRESS:
	// 		callback = shrapp_on_key;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	case MOUSE_RELEASE:
	// 		callback = shrapp_on_key;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	case WINDOW_UNFOCUS:
	// 		callback = shrwindow_on_unfocus;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	case WINDOW_FOCUS:
	// 		callback = shrwindow_on_focus;
	// 		pass_data = &app->input_state;
	// 		break;
	// 	default: break;
	// }
	//
	// bool dispatched = shrevent_dispatch(event, event->type, callback, pass_data);
	//
	// if (!dispatched) {
	//
	// 	usize layer_amount = shrlayer_stack_size(&app->layer_stack);
	//
	// 	for (usize i = layer_amount; i > 0; i--) {
	//
	// 		shrlayer *layer = shrlayer_stack_get(&app->layer_stack, i-1);
	//
	// 		if (layer->on_event) {
	//
	// 			dispatched = shrevent_dispatch(event, event->type, layer->on_event, app);
	// 		}
	// 		// If the event has been handled we don't want to propagate it further.
	// 		if (dispatched) break;
	// 	}
	// }
}

bool shrapp_on_key(u16 code, void *sender, void *listener, const sapp_event *data) {

	if (code == EVENT_KEY_PRESS) {
		
		u16 key_code = data->key_code;
		if (key_code == KEY_A) {
			TC_TRACE("A PRESSED!");
		}
	}

	return false;
}

// bool shrapp_on_quit(const shrevent *event, void *data) {
//
// 	(void)event;
//
// 	shrapp *app = (shrapp*)data;
//
// 	sapp_cancel_quit();
// 	shrapp_quit(app);
//
// 	return true;
// }
//
// bool shrapp_on_key(const shrevent *event, void *data) {
//
// 	shrinput_state *state = (shrinput_state*)data;
// 	shrinput_state_handle_event(state, event);
//
// 	return false;
// }

void shrapp_set_scene(shrapp *app, const char *name) {

	for (usize i = 0; i <= app->scene_list.used; i++) {

		if (app->scene_list.scenes[i]->name == name) {

			TC_INFO("Set scene to: %s", name);

			app->current_scene = app->scene_list.scenes[i];
			break;
		}
	}
}

// void shrapp_layer_push(shrapp *app, shrlayer *layer) {
	// shrlayer_stack_push(&app->layer_stack, layer);
	// darray_push(app->layers, layer);
// }

void shrapp_layer_new(shrapp *app, void *on_attach, void *on_detach, void *on_update) {

	shrlayer layer;
	layer.on_attach = on_attach;
	layer.on_update = on_update;
	layer.on_detach = on_detach;

	if (layer.on_attach) layer.on_attach(app);
	darray_push(app->layers, layer);
}

// void shrapp_overlay_push(shrapp *app, shrlayer *layer) {
// 	shrlayer_stack_push_front(&app->layer_stack, layer);
// }

void shrapp_destroy(shrapp *app) {

	shrevent_unregister(EVENT_APP_QUIT, 0, shrapp_on_event);
	shrevent_unregister(EVENT_KEY_PRESS, 0, shrapp_on_key);
	shrevent_unregister(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	shrscene_list_destroy(&app->scene_list);
	darray_destroy(app->layers);
	// shrlayer_stack_destory(&app->overlay_stack);

	shrevent_shutdown();
	shrinput_shutdown();
	free(app);
	app = NULL;

	TC_INFO("Destroyed App.");
}

// Sokol callback functions.

void sokol_init(void) {

	shrapp *app = (shrapp*)sapp_userdata();

	shrrenderer_init(&app->renderer);
	shrapp_init((shrapp*)sapp_userdata());
}

void sokol_frame(void) {

	shrapp *app = (shrapp*)sapp_userdata();

	shrapp_run(app);
	shrrenderer_begin(&app->renderer);
	shrapp_draw(app);
	shrrenderer_end();
}

void sokol_cleanup(void) {

	shrapp_cleanup((shrapp*)sapp_userdata());
	shrrenderer_cleanup();
	sg_shutdown();

	TC_INFO("Terminating Engine.");
}

// Handle the event data sokol gives out.
void sokol_event_callback(const sapp_event *e) {

	// shrevent event;
	shrapp* app = (shrapp*)sapp_userdata();

	switch (e->type) {
		// default:
			// event = shrevent_new(EVENT_NONE, e); break;
		case SAPP_EVENTTYPE_KEY_DOWN:
		case SAPP_EVENTTYPE_KEY_UP: {
			bool pressed = (e->type == SAPP_EVENTTYPE_KEY_DOWN);
			shrinput_process_key(e, pressed);
			break;
		}
			// shrevent_fire(&app->event_state, EVENT_KEY_RELEASE, 0, e); break;
			// event = shrevent_new(KEY_RELEASE, e); break;
		// case SAPP_EVENTTYPE_MOUSE_MOVE:
			// event = shrevent_new(MOUSE_MOVE, e); break;
		// case SAPP_EVENTTYPE_MOUSE_SCROLL:
			// event = shrevent_new(MOUSE_SCROLL, e); break;
		case SAPP_EVENTTYPE_MOUSE_DOWN:
		case SAPP_EVENTTYPE_MOUSE_UP: {
			bool pressed = (e->type == SAPP_EVENTTYPE_MOUSE_DOWN);
			shrinput_process_button(e, pressed);
			break;
		}
			// event = shrevent_new(MOUSE_RELEASE, e); break;
		// case SAPP_EVENTTYPE_RESIZED:
			// event = shrevent_new(WINDOW_RESIZE, e); break;
		case SAPP_EVENTTYPE_QUIT_REQUESTED:
			shrevent_fire(EVENT_APP_QUIT, 0, e); break;
			// event = shrevent_new(WINDOW_CLOSE, e); break;
		// case SAPP_EVENTTYPE_FOCUSED:
			// event = shrevent_new(WINDOW_FOCUS, e); break;
		// case SAPP_EVENTTYPE_UNFOCUSED:
			// event = shrevent_new(WINDOW_UNFOCUS, e); break;
		default: break;
	}

	// shrapp_on_event(&event, sapp_userdata());
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
		case 0: TC_FATAL("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 1: TC_ERROR("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 2: TC_WARN("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 3: TC_INFO("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
	}
}
