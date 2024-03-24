#include "application.h"
#include "packer.h"

void sk_init(void) {

    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });

}

void sk_frame(void) {

    sg_begin_pass(&(sg_pass){.action = (sg_pass_action) {
        .colors[0] = { .load_action=SG_LOADACTION_CLEAR, .clear_value={0.0f, 0.0f, 0.0f, 1.0f } }
    }, .swapchain = sglue_swapchain() });
    sg_end_pass();
    sg_commit();
}

void sk_cleanup(void) {

    sg_shutdown();
	tc_app_cleanup();
}

App* tc_app_new() {

	TC_INFO("Creating App.");

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->scene_list = scene_list_new();
	app->state = APP_RUNNING;

	// pac("assets");

	return app;
}

void tc_app_on_event(Event *e) {

	TC_INFO("%d", e);
	// Dispatch event.
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
	// window_destroy(&app->window);
	free(app);
	app = NULL;

	TC_INFO("Destroyed App.");
}
