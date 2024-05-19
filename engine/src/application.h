#ifndef APPLICATION_H
#define APPLICATION_H

#include "shrpch.h"
#include "input.h"
#include "window.h"
#include "layer.h"
#include "scene.h"
#include "renderer/renderer.h"

typedef enum {

	APP_STATE_RUNNING,
	APP_STATE_UNFOCUSED,
	APP_STATE_PAUSED,
	APP_STATE_QUIT_REQUESTED,
	APP_STATE_QUIT,
	
} shrapp_state;

typedef struct {

	shrrenderer renderer;

	shrwindow window;
	shrevent_state event_state;
	shrapp_state state;
	shrinput_state input_state;

	shrlayer_stack layer_stack;
	shrlayer_stack overlay_stack;

	shrscene_list scene_list;
	shrscene *current_scene;

	u32 fps;
} shrapp;

shrapp* shrapp_new();
void shrapp_run(void *data);
shrapp* shrapp_create(); // Defined in client.
void shrapp_destroy(shrapp *app);
// void shrapp_on_event(shrevent *event, void *data);
bool shrapp_on_event(u16 code, void *sender, void *listener, const sapp_event *data);
bool shrapp_check_state(shrapp *app, shrapp_state state);
void shrapp_set_scene(shrapp *app, const char *name);
void shrapp_quit(shrapp *app);

void shrapp_layer_push(shrapp *app, shrlayer *layer);
void shrapp_overlay_push(shrapp *app, shrlayer *layer);

// Event callbacks.
bool shrapp_on_quit(const shrevent *event, void *data);
bool shrapp_on_key(const shrevent *event, void *data);

// Defined in user implementation.
extern void shrapp_init(shrapp *app);
extern void shrapp_update(shrapp *app);
extern void shrapp_draw(shrapp *app);
extern void shrapp_cleanup(shrapp *app);

// Sokol callback functions.
void sokol_init(void);
void sokol_frame(void);
void sokol_cleanup(void);
void sokol_event_callback(const sapp_event *e);
void sokol_log_callback(
        const char* tag,                // always "sapp"
        u32 log_level,             // 0=panic, 1=error, 2=warning, 3=info
        u32 log_item_id,           // SAPP_LOGITEM_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        u32 line_nr,               // line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data);

#endif // !APPLICATION_H
