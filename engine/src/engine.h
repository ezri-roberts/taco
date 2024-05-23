#ifndef ENGINE_H
#define ENGINE_H

#include "application.h"

// These are provided as casllbacks to sokol.
void engine_initialize(void);
void engine_update(void);
void engine_shutdown(void);
void engine_event(const sapp_event *e);
void engine_log_callback(
        const char* tag,                // always "sapp"
        u32 log_level,             		// 0=panic, 1=error, 2=warning, 3=info
        u32 log_item_id,           		// SAPP_LOGITEM_*
        const char* message_or_null,	// a message string, may be nullptr in release mode
        u32 line_nr,               		// line number in sokol_app.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data);

#endif // !ENGINE_H
