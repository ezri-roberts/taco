#include "taco/window.h"

Window window_new(const char *title, uint32_t width, uint32_t height) {

	TC_TRACE("Creating Window.");

	Window window;

	window.data.title = title;
	window.data.width = width;
	window.data.height = height;
	window.data.target_fps = 60;

	InitWindow(width, height, title);
	SetTargetFPS(window.data.target_fps);
	window.handle = GetWindowHandle();

	return window;
}

void window_on_update(Window *window) {

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

		ClearBackground((Color){50, 50, 50, 255});

		EndDrawing();
	}

}

void window_destroy(Window *window) {

	CloseWindow();
	TC_TRACE("Destroyed window.");
}
