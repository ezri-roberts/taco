#include "application.h"

App *tc_app_new() {

	App *app = malloc(sizeof(App));

	app->window = window_new("Game Window", 1280, 720);
	app->running = true;

	TC_TRACE("Created app.");

	return app;
}

void tc_app_run(App *app) {

	// TC_INFO("Starting app loop.");
	// while (!window_should_close(app->window)) {
	
	window_on_update(&app->window);

}

void tc_app_destroy(App *app) {

	window_destroy(&app->window);
	free(app);
	app = NULL;

	TC_TRACE("Destroyed app.");
}
