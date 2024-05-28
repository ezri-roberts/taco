#include "application.h"
#include "window.h"

static shrapp app = {};
static bool initialized = false;

bool shrapp_initialize() {

	memset(&app, 0, sizeof(shrapp));
	initialized = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SHR_ERROR("SDL initialization failed: %s", SDL_GetError());
		return 1;
	}

	if (!shrwindow_initialize("Shraybn", 1280, 720)) {
		SHR_ERROR("Window initialization failed.");
		return false;
	}

	// if (!shrevent_initialize()) {
	// 	SHR_ERROR("Event system initialization failed.");
	// 	return false;
	// }
	//
	// if (!shrinput_initialize()) {
	// 	SHR_ERROR("Input system initialization failed.");
	// 	return false;
	// }
	//
	if (!shrrenderer_initialize()) {
		SHR_ERROR("Renderer initialization failed.");
		return false;
	}

	// shrevent_register(EVENT_APP_QUIT, 0, shrapp_on_event);
	// shrevent_register(EVENT_WINDOW_UNFOCUS, 0, shrapp_on_event);
	// shrevent_register(EVENT_WINDOW_FOCUS, 0, shrapp_on_event);
	// shrevent_register(EVENT_KEY_PRESS, 0, shrapp_on_key);
	// shrevent_register(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	app.layers = darray_create(shrlayer*);
	
	app.running = true;
	app.suspended = false;

	SHR_INFO("App initialized.");
	return true;
}

void shrapp_shutdown() {

	// shrevent_unregister(EVENT_APP_QUIT, 0, shrapp_on_event);
	// shrevent_unregister(EVENT_WINDOW_UNFOCUS, 0, shrapp_on_event);
	// shrevent_unregister(EVENT_WINDOW_FOCUS, 0, shrapp_on_event);
	// shrevent_unregister(EVENT_KEY_PRESS, 0, shrapp_on_key);
	// shrevent_unregister(EVENT_KEY_RELEASE, 0, shrapp_on_key);

	for (usize i = 0; i < darray_length(app.layers); i++) {
		shrlayer *layer = app.layers[i];
		if (layer->on_detach) layer->on_detach(0);
	}
	darray_destroy(app.layers);

	shrevent_shutdown();
	shrinput_shutdown();
	shrrenderer_shutdown();
	shrwindow_shutdown();

	SHR_INFO("App shutdown.");
	initialized = false;
}

bool shrapp_run() {

	if (!initialized) {
		SHR_ERROR("App not initialized.");
		return false;
	}

	while (app.running) {
		if (!app.suspended) {

			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						app.running = false;
					break;
					default: break;
				}
			}
		}
	}

	// if (app.running) {
	// 	if (!app.suspended) {
	//
	// 		usize layer_amount = darray_length(app.layers);
	//
	// 		// Run layer update callbacks.
	// 		for (usize i = 0; i < layer_amount; i++) {
	//
	// 			shrlayer *layer = app.layers[i];
	// 			if (layer->on_update) layer->on_update(0);
	// 		}
	//
	// 		shrapp_update();
	// 		shrinput_update();
	//
	// 		// shrrenderer_begin();
	// 		//
	// 		// // Run layer draw callbacks.
	// 		// for (usize i = 0; i < layer_amount; i++) {
	// 		//
	// 		// 	shrlayer *layer = app.layers[i];
	// 		// 	if (layer->on_draw) layer->on_draw(0);
	// 		// }
	// 		//
	// 		// shrapp_draw();
	// 		// shrrenderer_end();
	//
	// 		shrtimestep_end(app.timestep);
	// 	}
	//
	// 	return true;
	// }

	// sapp_quit();
	return true;
}

// bool shrapp_on_event(u16 code, void *sender, void *listener, const sapp_event *data) {
//
// 	switch (code) {
// 		case EVENT_APP_QUIT: {
// 			SHR_INFO("[EVENT][WINDOW_CLOSE] recieved, shutting down.");
// 			app.running = false;
// 			return true;
// 		}
// 		case EVENT_WINDOW_UNFOCUS: {
// 			SHR_INFO("[EVENT][WINDOW_UNFOCUS] recieved.");
// 			app.suspended = true;
// 			return true;
// 		}
// 		case EVENT_WINDOW_FOCUS: {
// 			SHR_INFO("[EVENT][WINDOW_FOCUS] recieved.");
// 			app.suspended = false;
// 			return true;
// 		}
// 	}
//
// 	// Was not handled.
// 	return false;
// }
//
// bool shrapp_on_key(u16 code, void *sender, void *listener, const sapp_event *data) {
//
// 	// Was not handled.
// 	return false;
// }
//
void shrapp_layer_new(const char *name, shrlayer_desc desc) {

	shrlayer *layer = shrlayer_new(name);
	if (desc.on_attach) {layer->on_attach = desc.on_attach;}
	if (desc.on_detach) {layer->on_detach= desc.on_detach;}
	if (desc.on_update) {layer->on_update = desc.on_update;}
	if (desc.on_draw)   {layer->on_draw = desc.on_draw;}

	if (layer->on_attach) {layer->on_attach(0);}
	darray_push(app.layers, layer);
}

shrapp* shrapp_get() {
	return &app;
}

void shrapp_quit() {
	app.running = false;
}
