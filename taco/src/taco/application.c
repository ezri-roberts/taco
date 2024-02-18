#include "application.h"

App *tc_app_new() {

	TC_TRACE("Creating app.");

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->running = true;

	return app;
}

void tc_app_run(App *app) {

	window_on_update(&app->window);
}

void tc_app_destroy(App *app) {

	window_destroy(&app->window);
	free(app);
	app = NULL;

	TC_TRACE("Destroyed app.");
}
