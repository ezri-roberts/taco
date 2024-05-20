#include "canvas.h"

shrcanvas shrcanvas_new(u32 width, u32 height) {

	shrcanvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.on_update = NULL;

	SHR_TRACE("Created Canvas.");

	return canvas;
}

void shrcanvas_update(shrcanvas *canvas) {

	if (canvas->on_update) canvas->on_update();
}
