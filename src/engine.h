#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

#include "window.h"

typedef struct {

	Window window;

	uint16_t fps;
	uint16_t fps_limit;
	float delta_time;

	int gl_version;

	// Sprite sprites[100];
	// int sprites_len;
	//
	// Canvas canvases[100];
	// int canvases_len;
} Engine;

extern Engine engine;

void engine_init();
void engine_update();
void engine_cleanup();

#endif // !ENGINE_H
