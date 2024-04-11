#ifndef CANVAS_H
#define CANVAS_H

#include "shrpch.h"
#include "engine/window.h"

typedef struct {

	void (*on_update)();
} shrcanvas;

shrcanvas shrcanvas_new(int width, int height);
void shrcanvas_update(shrcanvas *canvas);
void shrcanvas_draw(shrcanvas *canvas, shrwindow_data *win_data);

#endif // !CANVAS_H
