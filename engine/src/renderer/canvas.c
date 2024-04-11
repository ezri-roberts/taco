#include "canvas.h"

shrcanvas shrcanvas_new(int width, int height) {

	shrcanvas canvas;

	canvas.on_update = NULL;

	TC_TRACE("Created Canvas.");

	return canvas;
}

void shrcanvas_update(shrcanvas *canvas) {

	if (canvas->on_update) canvas->on_update();
}

void shrcanvas_draw(shrcanvas *canvas, shrwindow_data *win_data) {

}
