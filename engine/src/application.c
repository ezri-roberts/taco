#include "application.h"

shrapp* shrapp_new() {

	TC_INFO("Initializing Engine.");
	TC_INFO("Creating App.");

	shrapp *app = malloc(sizeof(shrapp));

	app->window = shrwindow_new("Game Window", 1280, 720);
	app->scene_list = shrscene_list_new();
	app->layer_stack = shrlayer_stack_new();
	app->overlay_stack = shrlayer_stack_new();
	app->state = APP_STATE_RUNNING;
	app->input_state = shrinput_state_new();

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

	size_t layer_amount = shrlayer_stack_size(&app->layer_stack);

	for (int i = 0; i <= layer_amount-1; i++) {

		shrlayer *layer = shrlayer_stack_get(&app->layer_stack, i);
		if (layer->on_update) layer->on_update(app);
	}

	shrinput_state_update(&app->input_state);
}

void shrapp_on_event(shrevent *event, void *data) {

	shrapp *app = (shrapp*)data;
	shrevent_callback callback = NULL;
	void *pass_data = data;

	switch (event->type) {
		case WINDOW_CLOSE:
			callback = shrapp_on_quit;
			break;
		case WINDOW_RESIZE:
			callback = shrwindow_on_resize;
			pass_data = &app->window.data;
			break;
		case KEY_PRESS:
			callback = shrapp_on_key;
			pass_data = &app->input_state;
			break;
		case KEY_RELEASE:
			callback = shrapp_on_key;
			pass_data = &app->input_state;
			break;
		case MOUSE_PRESS:
			callback = shrapp_on_key;
			pass_data = &app->input_state;
			break;
		case MOUSE_RELEASE:
			callback = shrapp_on_key;
			pass_data = &app->input_state;
			break;
		case WINDOW_UNFOCUS:
			callback = shrwindow_on_unfocus;
			pass_data = &app->input_state;
			break;
		case WINDOW_FOCUS:
			callback = shrwindow_on_focus;
			pass_data = &app->input_state;
			break;
	}

	bool dispatched = shrevent_dispatch(event, event->type, callback, pass_data);

	if (!dispatched) {

		size_t layer_amount = app->layer_stack.used;

		for (int i = layer_amount-1; i >= 0; i--) {

			shrlayer *layer = shrlayer_stack_get(&app->layer_stack, i);

			if (layer->on_event) layer->on_event(event, app);
			// If the event has been handled we don't want to propagate it further.
			if (event->handled) break;
		}
	}
}

bool shrapp_on_quit(const shrevent *event, void *data) {

	shrapp *app = (shrapp*)data;

	sapp_cancel_quit();
	shrapp_quit(app);

	return true;
}

bool shrapp_on_key(const shrevent *event, void *data) {

	shrinput_state *state = (shrinput_state*)data;
	shrinput_state_handle_event(state, event);

	return false;
}

void shrapp_set_scene(shrapp *app, const char *name) {

	for (int i = 0; i <= app->scene_list.used; i++) {

		if (app->scene_list.scenes[i]->name == name) {

			TC_INFO("Set scene to: %s", name);

			app->current_scene = app->scene_list.scenes[i];
			break;
		}
	}
}

void shrapp_layer_push(shrapp *app, shrlayer *layer) {
	shrlayer_stack_push(&app->layer_stack, layer);
}

void shrapp_overlay_push(shrapp *app, shrlayer *layer) {
	shrlayer_stack_push_front(&app->layer_stack, layer);
}

void shrapp_destroy(shrapp *app) {

	shrscene_list_destroy(&app->scene_list);
	shrlayer_stack_destory(&app->overlay_stack);
	free(app);
	app = NULL;

	TC_INFO("Destroyed App.");
}

// Sokol callback functions.

void sokol_init(void) {

	shrapp *app = (shrapp*)sapp_userdata();
	shrapp_init((shrapp*)sapp_userdata());

	shrrenderer_init(&app->renderer);

	app->dbui.bg = (dbui_color){ 90.0f, 95.0f, 100.0f };
	dbui_init(&app->dbui);
}

void sokol_frame(void) {

	shrapp *app = (shrapp*)sapp_userdata();
	// DBUIState *dbui_state = &app->dbui_state;

	shrapp_run(app);
	shrapp_frame((shrapp*)sapp_userdata());

	shrrenderer_frame(&app->renderer);
	// dbui_update(&app->dbui_state);
	// mu_begin(&dbui_state->mu_ctx);
 //    dbui_test_window(dbui_state);
 //    mu_end(&dbui_state->mu_ctx);
	//
	// dbui_begin(sapp_width(), sapp_height());
	// mu_Command* cmd = 0;
	// while(mu_next_command(&dbui_state->mu_ctx, &cmd)) {
	// 	switch (cmd->type) {
	// 		case MU_COMMAND_TEXT: dbui_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
	// 		case MU_COMMAND_RECT: dbui_draw_rect(cmd->rect.rect, cmd->rect.color); break;
	// 		case MU_COMMAND_ICON: dbui_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
	// 		case MU_COMMAND_CLIP: dbui_set_clip_rect(cmd->clip.rect); break;
	// 	}
	// }
	// dbui_end();

    // sg_begin_pass(&(sg_pass){.action = state->pass_action, .swapchain = sglue_swapchain()});
	// dbui_draw();
    // sg_end_pass();
    // sg_commit();
}

void sokol_cleanup(void) {

	shrapp_cleanup((shrapp*)sapp_userdata());
	sgl_shutdown();
	sg_shutdown();

	TC_INFO("Terminating Engine.");
}

// Handle the event data sokol gives out.
void sokol_event_callback(const sapp_event *e) {

	shrapp *app = (shrapp*)sapp_userdata();

	shrevent event;

	// dbui_event(&app->dbui_state, e);

	switch (e->type) {
		default:
			event = shrevent_new(EVENT_NONE, e); break;
		case SAPP_EVENTTYPE_KEY_DOWN:
			event = shrevent_new(KEY_PRESS, e); break;
		case SAPP_EVENTTYPE_KEY_UP:
			event = shrevent_new(KEY_RELEASE, e); break;
		case SAPP_EVENTTYPE_MOUSE_MOVE:
			event = shrevent_new(MOUSE_MOVE, e); break;
		case SAPP_EVENTTYPE_MOUSE_SCROLL:
			event = shrevent_new(MOUSE_SCROLL, e); break;
		case SAPP_EVENTTYPE_MOUSE_DOWN:
			event = shrevent_new(MOUSE_PRESS, e); break;
		case SAPP_EVENTTYPE_MOUSE_UP:
			event = shrevent_new(MOUSE_RELEASE, e); break;
		case SAPP_EVENTTYPE_RESIZED:
			event = shrevent_new(WINDOW_RESIZE, e); break;
		case SAPP_EVENTTYPE_QUIT_REQUESTED:
			event = shrevent_new(WINDOW_CLOSE, e); break;
		case SAPP_EVENTTYPE_FOCUSED:
			event = shrevent_new(WINDOW_FOCUS, e); break;
		case SAPP_EVENTTYPE_UNFOCUSED:
			event = shrevent_new(WINDOW_UNFOCUS, e); break;
	}

	shrapp_on_event(&event, sapp_userdata());
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