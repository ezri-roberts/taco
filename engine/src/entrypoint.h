#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "engine.h"
#include "application.h"

#if defined(SHR_PLATFORM_LINUX) || defined(SHR_PLATFORM_WINDOWS)

inline sapp_desc sokol_main(int argc, char* argv[]) {

    (void)argc; (void)argv;

	shrwindow_data win_data;
	shrwindow_get_data(&win_data);

    return (sapp_desc){
        .init_cb = engine_initialize,
        .frame_cb = engine_update,
        .cleanup_cb = engine_shutdown,
		.event_cb = engine_event,
        .width = (int)win_data.width,
        .height = (int)win_data.height,
		.swap_interval = 0,					// 1 for vsync.
        .window_title = "Shraybn",
        .icon.sokol_default = true,
        .logger.func = engine_log_callback,
    };

}

#endif // !SHR_PLATFORM_LINUX
#endif // !ENTRYPOINT_H
