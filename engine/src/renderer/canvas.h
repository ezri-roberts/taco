#ifndef CANVAS_H
#define CANVAS_H

#include "shrpch.h"
#include "window.h"

typedef struct {

	u32 width;
	u32 height;

	void (*on_update)();
} shrcanvas;

shrcanvas shrcanvas_new(u32 width, u32 height);
void shrcanvas_update(shrcanvas *canvas);
void shrcanvas_draw(shrcanvas *canvas, shrwindow_data *win_data);

#endif // !CANVAS_H
