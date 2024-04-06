#include "taco.h"

App *app;

App* app_init() {

	app = app_new();

	return app;
}

void app_frame() {

	TC_TRACE("FRAME!");
}

void app_cleanup() {

	app_destroy(app);
}

// App *tc_app_create() {
//
// 	app = tc_app_new();
// 	
// 	return app;
// }

