#include "application.h"
// #include "packer.h"

App* app_new() {

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
	app->layer_stack = NULL;
	app->state = APP_STATE_RUNNING;

	// pack("assets/");

	return app;
}

bool app_check_state(App *app, AppState state) {
	return (app->state == state);
}

void app_quit(App *app) {
	app->state = APP_STATE_QUIT_REQUESTED;
}

void app_run(void *data) {

	App *app = (App*)data;

	if (app->state == APP_STATE_QUIT_REQUESTED) {
		sapp_quit();
	}

	if (app->layer_stack) { // Stack is null if no scene is currently active.

		int layer_amount = layer_stack_size(app->layer_stack);

		for (int i = 0; i <= layer_amount-1; i++) {

			Layer *layer = layer_stack_get(app->layer_stack, i);
			if (layer->on_update) layer->on_update();
		}
	}

	input_state_update(&app->input_state);

	if (key_is_released(SPACE)) {
		TC_TRACE("SPACE!");
	}	
}

void app_on_event(Event *e, void *data) {

	App *app = (App*)data;
	EventCallback callback = NULL;
	void *pass_data = data;


	switch (e->type) {
		case WINDOW_CLOSE:
			callback = app_on_quit;
			break;
		case WINDOW_RESIZE:
			callback = window_on_resize;
			pass_data = &app->window.data;
			break;
		case KEY_PRESS:
			callback = app_on_key;
			pass_data = &app->input_state;
			break;
		case KEY_RELEASE:
			callback = app_on_key;
			pass_data = &app->input_state;
			break;
	}

	bool dispatched = event_dispatch(e, e->type, callback, pass_data);

	// If dispatched event returns false, propagate it through the layers.
	if (!dispatched && app->layer_stack) {

		int layer_amount = layer_stack_size(app->layer_stack);

		for (int i = layer_amount; i > 0; i--) {

			Layer *layer = layer_stack_get(app->layer_stack, i);
			if (layer->on_event) layer->on_event(e, data);
			// If the event has been handled we don't want to propagate it further.
			if (e->handled) break;
		}
	}
}

bool app_on_quit(const Event *e, void *data) {

	App *app = (App*)data;

	sapp_cancel_quit();
	app_quit(app);

	return true;
}

bool app_on_key(const Event *e, void *data) {

	InputState *state = (InputState*)data;
	input_state_handle_event(state, e);

	return true;
}

void app_set_scene(App *app, const char *name) {

	for (int i = 0; i <= app->scene_list.used; i++) {

		if (app->scene_list.scenes[i]->name == name) {

			TC_INFO("Set scene to: %s", name);

			app->current_scene = app->scene_list.scenes[i];
			app->layer_stack = &app->current_scene->layer_stack;
			break;
		}
	}
}

void app_destroy(App *app) {

	scene_list_destroy(&app->scene_list);
	free(app);
	app = NULL;

	TC_INFO("Destroyed App.");
}

// Sokol callback functions.

void sokol_init(void) {

	App *app = (App*)sapp_userdata();
	app_init((App*)sapp_userdata());

    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });

	sgl_setup(&(sgl_desc_t){
        .logger.func = slog_func,
    });

	app->dbui_state.bg = (DBUIColor){ 90.0f, 95.0f, 100.0f };
	dbui_init(&app->dbui_state);

	app->render_state.pass_action = (sg_pass_action) {
        .colors[0] = {.load_action=SG_LOADACTION_CLEAR, .clear_value={0.0f, 0.0f, 0.0f, 1.0f}}
    };
}

void sokol_frame(void) {

	App *app = (App*)sapp_userdata();
	RenderState *state = &app->render_state;
	DBUIState *dbui_state = &app->dbui_state;

	app_run(app);
	app_frame((App*)sapp_userdata());

	mu_begin(&dbui_state->mu_ctx);
    dbui_test_window(dbui_state);
    mu_end(&dbui_state->mu_ctx);

	dbui_begin(sapp_width(), sapp_height());
	mu_Command* cmd = 0;
	while(mu_next_command(&dbui_state->mu_ctx, &cmd)) {
		switch (cmd->type) {
			case MU_COMMAND_TEXT: dbui_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
			case MU_COMMAND_RECT: dbui_draw_rect(cmd->rect.rect, cmd->rect.color); break;
			case MU_COMMAND_ICON: dbui_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
			case MU_COMMAND_CLIP: dbui_set_clip_rect(cmd->clip.rect); break;
		}
	}
	dbui_end();

    sg_begin_pass(&(sg_pass){.action = state->pass_action, .swapchain = sglue_swapchain()});
	dbui_draw();
    sg_end_pass();
    sg_commit();
}

void sokol_cleanup(void) {

	app_cleanup((App*)sapp_userdata());
	sgl_shutdown();
    sg_shutdown();

	TC_INFO("Terminating Engine.");
}

// Handle the event data sokol gives out.
void sokol_event_callback(const sapp_event *e) {

	App *app = (App*)sapp_userdata();

	Event event;

	dbui_event(&app->dbui_state, e);
	// TC_TRACE("%d", event.data.window_width);

	switch (e->type) {
		default:
			event = event_new(EVENT_NONE, e);
		case SAPP_EVENTTYPE_KEY_DOWN:
			event = event_new(KEY_PRESS, e); break;
		case SAPP_EVENTTYPE_KEY_UP:
			event = event_new(KEY_RELEASE, e); break;
		case SAPP_EVENTTYPE_MOUSE_MOVE:
			event = event_new(MOUSE_MOVE, e); break;
		case SAPP_EVENTTYPE_MOUSE_SCROLL:
			event = event_new(MOUSE_SCROLL, e); break;
		case SAPP_EVENTTYPE_MOUSE_DOWN:
			event = event_new(MOUSE_PRESS, e); break;
		case SAPP_EVENTTYPE_MOUSE_UP:
			event = event_new(MOUSE_RELEASE, e); break;
		case SAPP_EVENTTYPE_RESIZED:
			event = event_new(WINDOW_RESIZE, e); break;
		case SAPP_EVENTTYPE_QUIT_REQUESTED:
			event = event_new(WINDOW_CLOSE, e); break;
		case SAPP_EVENTTYPE_FOCUSED:
			event = event_new(WINDOW_FOCUS, e); break;
		case SAPP_EVENTTYPE_UNFOCUSED:
			event = event_new(WINDOW_UNFOCUS, e); break;
	}

	app_on_event(&event, sapp_userdata());
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
