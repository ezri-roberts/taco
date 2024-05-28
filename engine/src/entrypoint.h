#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "engine.h"
#include "application.h"

#include "glad/glad.h"
#include <SDL2/SDL.h>

#if defined(SHR_PLATFORM_LINUX) || defined(SHR_PLATFORM_WINDOWS)

int main(int argc, char **argv) {

	SHR_INFO("Initializing engine.");

	if (!shrapp_initialize()) {
		SHR_FATAL("Failed to create engine.");
		return 1;
	}

	bool quit = false;

	while (!quit) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default: break;
			}
		}
	}

	return 0;
}

// inline sapp_desc sokol_main(int argc, char* argv[]) {
//
//     (void)argc; (void)argv;
//
// 	shrwindow_data win_data;
// 	shrwindow_get_data(&win_data);
//
//     return (sapp_desc){
//         .init_cb = engine_initialize,
//         .frame_cb = engine_update,
//         .cleanup_cb = engine_shutdown,
// 		.event_cb = engine_event,
//         .width = (int)win_data.width,
//         .height = (int)win_data.height,
// 		.swap_interval = 0,					// 1 for vsync.
//         .window_title = "Shraybn",
//         .icon.sokol_default = true,
//         .logger.func = engine_log_callback,
//     };
//
// }

#endif // !SHR_PLATFORM_LINUX
#endif // !ENTRYPOINT_H
