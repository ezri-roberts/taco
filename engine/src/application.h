#ifndef APPLICATION_H
#define APPLICATION_H

#include "shrpch.h"
#include "input.h"
#include "window.h"
#include "layer.h"
#include "scene.h"
#include "timestep.h"
#include "renderer/renderer.h"
#include "renderer/camera.h"

typedef enum {

	APP_STATE_RUNNING,
	APP_STATE_UNFOCUSED,
	APP_STATE_PAUSED,
	APP_STATE_QUIT_REQUESTED,
	APP_STATE_QUIT,
	
} shrapp_state;

typedef struct {

	shrrenderer renderer;

	bool running;
	bool suspended;

	shrtimestep *timestep;

	shrlayer **layers;
	shrcamera *camera;
} shrapp;

bool shrapp_initialize();
bool shrapp_run();
void shrapp_shutdown();

bool shrapp_on_event(u16 code, void *sender, void *listener, shrevent_data *data);
// bool shrapp_on_key(u16 code, void *sender, void *listener, const sapp_event *data);
shrapp* shrapp_get();
void shrapp_quit();

void shrapp_layer_new(const char *name, shrlayer_desc desc);

// Defined in user implementation.
extern void shrapp_start();
extern void shrapp_update();
extern void shrapp_draw();
extern void shrapp_cleanup();

#endif // !APPLICATION_H
