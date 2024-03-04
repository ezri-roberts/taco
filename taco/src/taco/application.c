#include "application.h"

App *tc_app_new() {

	TC_TRACE("Creating app.");

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->layer_stack = layer_stack_new();
	app->running = true;

	window_set_event_callback(&app->window, tc_app_on_event);

	return app;
}

void tc_app_on_event(Event *e) {

	TC_INFO("%d", e);
	// Dispatch event.
}

void tc_app_run(App *app) {

	while (app->running) {

		if (WindowShouldClose()) app->running = false;

		BeginDrawing();
		ClearBackground((Color){50, 50, 50, 255});

		uint16_t layer_amount = app->layer_stack.length;

		for (int i = 0; i < layer_amount; i++) {
		
			Layer *layer = app->layer_stack.layers[i];
			layer_update(layer);
		}

		EndDrawing();

		window_on_update(&app->window);
	}

}

void tc_app_destroy(App *app) {

	window_destroy(&app->window);
	free(app);
	app = NULL;

	TC_TRACE("Destroyed app.");
}
