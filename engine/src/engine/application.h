#ifndef APPLICATION_H
#define APPLICATION_H

#include "tcpch.h"
#include "input.h"
#include "window.h"
#include "layer.h"
#include "scene.h"
#include "dbui/dbui.h"

typedef enum {

	APP_STATE_RUNNING,
	APP_STATE_UNFOCUSED,
	APP_STATE_PAUSED,
	APP_STATE_QUIT_REQUESTED,
	APP_STATE_QUIT,
	
} AppState;

typedef struct {

	sg_pass_action pass_action;
} RenderState;

typedef struct {

	RenderState render_state;
	DBUIState dbui_state;

	TcWindow window;
	LayerStack *layer_stack;
	AppState state;

	SceneList scene_list;
	Scene *current_scene;

	uint32_t fps;
} App;

App* app_new();
void app_run(App *app);
App* app_create(); // Defined in client.
void app_destroy(App *app);
void app_on_event(Event *e, void *data);
bool app_check_state(App *app, AppState state);
void app_set_scene(App *app, const char *name);
void app_quit(App *app);

// Event callbacks.
bool app_on_quit(const Event *e, void *data);
bool app_on_key(const Event *e, void *data);

// Defined in user implementation.
extern App* app_init(void);
extern void app_frame(void);
extern void app_cleanup(void);

// Sokol callback functions.
void sokol_init(void);
void sokol_frame(void);
void sokol_cleanup(void);
void sokol_event_callback(const sapp_event *e);
void sokol_log_callback(
        const char* tag,                // always "sapp"
        uint32_t log_level,             // 0=panic, 1=error, 2=warning, 3=info
        uint32_t log_item_id,           // SAPP_LOGITEM_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        uint32_t line_nr,               // line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data);

#endif // !APPLICATION_H
