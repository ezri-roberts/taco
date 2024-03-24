#ifndef APPLICATION_H
#define APPLICATION_H

#include "tcpch.h"
#include "input.h"
#include "taco/window.h"
#include "taco/layer.h"
#include "taco/scene.h"

typedef enum {

	APP_RUNNING,
	APP_UNFOCUSED,
	APP_PAUSED,
	APP_QUIT_REQUESTED,
	APP_QUIT,
	
} AppState;

typedef struct {

	sg_pass_action pass_action;
} RenderState;

typedef struct {

	RenderState render_state;

	TcWindow window;
	LayerStack *layer_stack;
	AppState state;

	SceneList scene_list;
	Scene *current_scene;

	uint32_t fps;
} App;

App* tc_app_new();
void tc_app_run(App *app);
App* tc_app_create(); // Defined in client.
void tc_app_destroy(App *app);
void tc_app_on_event(Event *e);
bool tc_app_check_state(App *app, AppState state);
void tc_app_set_scene(App *app, const char *name);
void tc_app_quit(App *app);
void sk_init(void);
void sk_frame(void);
void sk_cleanup(void);
App* tc_app_init(void);
void tc_app_frame(void);
void tc_app_cleanup(void);

#endif // !APPLICATION_H
