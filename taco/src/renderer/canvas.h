#ifndef CANVAS_H
#define CANVAS_H

#include "tcpch.h"
#include "taco/window.h"

typedef struct {

	// RenderTexture2D target;
	// Rectangle source;
	// Rectangle dest;
	void (*on_update)();
} Canvas;

Canvas canvas_new(int width, int height);
void canvas_update(Canvas *canvas);
void canvas_draw(Canvas *canvas, TcWindowData *win_data);

#endif // !CANVAS_H
