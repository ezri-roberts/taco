#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "taco/application.h"

#if defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_WINDOWS)

extern App* app_create();
extern App* tc_app_init(void);
extern void tc_app_frame(void);
extern void tc_app_cleanup(void);

inline sapp_desc sokol_main(int argc, char* argv[]) {

	TC_INFO("Initializing Engine.");

	// App *app = tc_app_create();
	App *app = tc_app_init();

	TcWindowData *win_data = &app->window.data;

    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = sk_init,
        .frame_cb = sk_frame,
        .cleanup_cb = sk_cleanup,
        .width = (int)win_data->width,
        .height = (int)win_data->height,
        .window_title = win_data->title,
        .icon.sokol_default = true,
        .logger.func = slog_func,
    };
}

// int main (int argc, char *argv[]) {
//
// 	TC_INFO("Initializing Engine.");
// 	
// 	App *app = tc_app_create();
// 	tc_app_run(app);
//
// 	TC_INFO("Terminating Engine.");
// 	tc_app_destroy(app);
//
// 	return 0;
// }

#endif // !TC_PLATFORM_LINUX

#endif // !ENTRYPOINT_H
