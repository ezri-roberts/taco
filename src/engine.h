#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include "canvas.h"
#include "image.h"

typedef struct {

	uint16_t window_width;
	uint16_t window_height;
	char	*window_title;

	uint16_t fps;
	uint16_t fps_limit;
	float delta_time;

	Sprite sprites[100];
	int sprites_len;

	Canvas canvases[100];
	int canvases_len;
} Engine;

extern Engine engine;

/*
 * local canvas = Canvas.new(128, 128)
 * Canvas.resize(canvas, 1280, 720)
*/

void engine_init();
void engine_update();
void engine_cleanup();
void window_set_size(uint16_t w, uint16_t h);

#endif // !ENGINE_H
