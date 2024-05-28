#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "engine.h"
#include "application.h"

#include "glad/glad.h"
#include <SDL2/SDL_video.h>
#define SLD_MAIN_HANDLED
#include <SDL2/SDL.h>

#if defined(SHR_PLATFORM_LINUX) || defined(SHR_PLATFORM_WINDOWS)

int main(int argc, char **argv) {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SHR_ERROR("SDL failed to initialize: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"Shraybn",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_OPENGL
	);

	if (!window) {
		SHR_ERROR("Window failed to initialize: %s", SDL_GetError());
		return 1;
	}

	SDL_GL_CreateContext(window);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SHR_ERROR("GL failed to load: %s", SDL_GetError());
		return 1;
	}

	SHR_INFO("OpenGL loaded.");
	SHR_INFO("Vendor:   %s", glGetString(GL_VENDOR));
	SHR_INFO("Renderer: %s", glGetString(GL_RENDERER));
	SHR_INFO("Version:  %s", glGetString(GL_VERSION));

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
