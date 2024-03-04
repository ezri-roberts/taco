#ifndef APPLICATION_H
#define APPLICATION_H

#include "tcpch.h"
#include "taco/window.h"
#include "taco/layer.h"

typedef struct {

	Window window;
	LayerStack layer_stack;
	bool running;
} App;

App *tc_app_new();
void tc_app_run(App *app);
App *tc_app_create(); // Defined in client.
void tc_app_destroy(App *app);

#endif // !APPLICATION_H
