#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "taco/application.h"

#if defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_WINDOWS)

extern App* app_create();

inline void sk_init(void) {

	sg_setup(&(sg_desc) {
		.environment = sglue_environment(),
		.logger.func = slog_func,
	});

}

void sk_frame(void) {

	sg_begin_pass(&(sg_pass){.swapchain = sglue_swapchain()});
	sg_end_pass();
	sg_commit();
}

void sk_cleanup(void) {

	sg_shutdown();
}


inline sapp_desc sokol_main(int argc, char* argv[]) {

	TC_INFO("Initializing Engine.");

	App *app = tc_app_create();

    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = sk_init,
        .frame_cb = sk_frame,
        .cleanup_cb = sk_cleanup,
        .width = 640,
        .height = 480,
        .window_title = "Triangle",
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
