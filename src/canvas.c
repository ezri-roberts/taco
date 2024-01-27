#include "engine.h"
#include "canvas.h"
#include "raylib.h"

Canvas *canvas_new(int width, int height, int filter_mode) {

    Canvas canvas = {
        .target = LoadRenderTexture(width, height),
    };

    SetTextureFilter(canvas.target.texture, filter_mode);

    engine.canvases[engine.canvases_len] = &canvas;
    engine.canvases_len ++;

    return engine.canvases[engine.canvases_len - 1];
}

void canvas_begin(Canvas *canvas) {
    BeginTextureMode(canvas->target);
    ClearBackground(BLACK);
}

void canvas_end(Canvas *canvas) {
    EndTextureMode();
}
