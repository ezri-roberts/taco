#include "engine.h"

void engine_initialize(void) {

	SHR_INFO("Initializing engine.");

	if (!shrapp_initialize()) {
		SHR_FATAL("Failed to create engine.");
		exit(1);
	}

	shrapp_start();
}

void engine_shutdown(void) {
	shrapp_shutdown();
	// sg_shutdown();
	SHR_INFO("Engine shutdown.");
}

void engine_update(void) {
	if (!shrapp_run()) {
		SHR_FATAL("Application did not exit gracefully.");
		exit(1);
	}
}

// void engine_event(const sapp_event *e) {
//
// 	switch (e->type) {
// 		case SAPP_EVENTTYPE_KEY_DOWN:
// 		case SAPP_EVENTTYPE_KEY_UP: {
// 			bool pressed = (e->type == SAPP_EVENTTYPE_KEY_DOWN);
// 			shrinput_process_key(e, pressed);
// 			break;
// 		}
// 		case SAPP_EVENTTYPE_MOUSE_DOWN:
// 		case SAPP_EVENTTYPE_MOUSE_UP: {
// 			bool pressed = (e->type == SAPP_EVENTTYPE_MOUSE_DOWN);
// 			shrinput_process_button(e, pressed);
// 			break;
// 		}
// 		case SAPP_EVENTTYPE_MOUSE_MOVE:
// 			shrinput_process_mouse_move(e);
// 		case SAPP_EVENTTYPE_MOUSE_SCROLL:
// 			shrinput_process_mouse_wheel(e);
// 		case SAPP_EVENTTYPE_MOUSE_ENTER:
// 			shrevent_fire(EVENT_MOUSE_ENTER, 0, e); break;
// 		case SAPP_EVENTTYPE_MOUSE_LEAVE:
// 			shrevent_fire(EVENT_MOUSE_LEAVE, 0, e); break;
// 		case SAPP_EVENTTYPE_QUIT_REQUESTED:
// 			shrevent_fire(EVENT_APP_QUIT, 0, e); break;
// 		case SAPP_EVENTTYPE_CHAR:
// 			shrevent_fire(EVENT_CHAR, 0, e); break;
// 		case SAPP_EVENTTYPE_RESIZED:
// 			shrwindow_process_resize(e); break;
// 		case SAPP_EVENTTYPE_UNFOCUSED:
// 			shrevent_fire(EVENT_WINDOW_UNFOCUS, 0, e); break;
// 		case SAPP_EVENTTYPE_FOCUSED:
// 			shrevent_fire(EVENT_WINDOW_FOCUS, 0, e); break;
// 		default: break;
// 	}
// }

void engine_log_callback(
        const char* tag,                // always "sapp"
        u32 log_level,             		// 0=panic, 1=error, 2=warning, 3=info
        u32 log_item_id,           		// sapp_logitem_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        u32 line_nr,               		// line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data) {

	(void)log_level; (void)log_item_id; (void)filename_or_null; (void)user_data;

	switch (log_level) {
		case 0: SHR_FATAL("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 1: SHR_ERROR("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 2: SHR_WARN("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
		case 3: SHR_INFO("[%s][sokol_app.h:%d] %s", tag, line_nr, message_or_null); break;
	}
}
