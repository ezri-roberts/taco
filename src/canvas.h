#ifndef CANVAS_H
#define CANVAS_H

#include "raylib.h"

typedef struct {

	RenderTexture2D target;
	Rectangle source;
	Rectangle dest;

} Canvas;

Canvas *canvas_new(int width, int height, int filter_mode);
void canvas_begin(Canvas *canvas);
void canvas_end(Canvas *canvas);

#endif // !CANVAS_H
