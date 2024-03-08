#include "application.h"
#include "renderer/canvas.h"

App* tc_app_new() {

	TC_TRACE("Creating app.");

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->layer_stack = layer_stack_new();
	app->state = APP_RUNNING;

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


}

void tc_app_run(App *app) {

	Canvas canvas = canvas_new(480, 270);

	while (app->state == APP_RUNNING) {

		if (WindowShouldClose()) app->state = APP_QUIT;

		canvas_update(&canvas);

		BeginDrawing();
		ClearBackground((Color){50, 50, 50, 255});

		canvas_draw(&canvas, &app->window.data);

		uint16_t layer_amount = app->layer_stack.layer_index;

		for (int i = 0; i <= layer_amount-1; i++) {

			Layer *layer = app->layer_stack.layers[i];
			if (layer->on_update) layer->on_update(GetFrameTime());
		}

		EndDrawing();

		window_on_update(&app->window);
	}

}

void tc_app_destroy(App *app) {

	layer_stack_destory(&app->layer_stack);
	window_destroy(&app->window);
	free(app);
	app = NULL;

	TC_TRACE("Destroyed app.");
}
