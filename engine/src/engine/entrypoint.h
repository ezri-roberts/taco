#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "engine/application.h"

#if defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_WINDOWS)

inline sapp_desc sokol_main(int argc, char* argv[]) {

    (void)argc; (void)argv;

	TC_INFO("Initializing Engine.");

	App *app = tc_app_init();
	TcWindowData *win_data = &app->window.data;

    return (sapp_desc){
        .init_cb = sokol_init,
        .frame_cb = sokol_frame,
        .cleanup_cb = sokol_cleanup,
        .width = (int)win_data->width,
        .height = (int)win_data->height,
        .window_title = win_data->title,
        .icon.sokol_default = true,
        .logger.func = slog_func,
    };
}

#endif // !TC_PLATFORM_LINUX
#endif // !ENTRYPOINT_H
