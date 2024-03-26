#include "taco.h"

App *app;

App* tc_app_init() {

	app = tc_app_new();

	return app;
}

void tc_app_frame() {

}

void tc_app_cleanup() {

	tc_app_destroy(app);
}

// App *tc_app_create() {
//
// 	app = tc_app_new();
// 	
// 	return app;
// }

