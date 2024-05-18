#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "application.h"

#if defined(SHR_PLATFORM_LINUX) || defined(SHR_PLATFORM_WINDOWS)

inline sapp_desc sokol_main(int argc, char* argv[]) {

    (void)argc; (void)argv;

	shrapp *app = shrapp_new();
	shrwindow_data *win_data = &app->window.data;

    return (sapp_desc){
        .init_cb = sokol_init,
        .frame_cb = sokol_frame,
        .cleanup_cb = sokol_cleanup,
		.event_cb = sokol_event_callback,
		.user_data = app,
        .width = (int)win_data->width,
        .height = (int)win_data->height,
		.swap_interval = 1,					// 1 for vsync.
        .window_title = win_data->title,
        .icon.sokol_default = true,
        .logger.func = sokol_log_callback,
    };

}

#endif // !SHR_PLATFORM_LINUX
#endif // !ENTRYPOINT_H
