#include <stdio.h>
#include "raylib.h"
#include "engine.h"

void engine_init() {

    engine.sprites_len = 0;
    engine.canvases_len = 0;

    engine.window_width = 1280;
    engine.window_height = 720;
    engine.window_title = "Game Window";

    InitWindow(engine.window_width, engine.window_height, engine.window_title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    engine.fps_limit = 60;
    engine.delta_time = 0;
    SetTargetFPS(engine.fps_limit);
}

void engine_update() {

    while (!WindowShouldClose()) {

        engine.delta_time = GetFrameTime();

        BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangle(32, 32, 128, 128, RAYWHITE);

        EndDrawing();
    }
}

void engine_cleanup() {

    CloseWindow();
}

void window_set_size(uint16_t w, uint16_t h) {
    engine.window_width = w;
    engine.window_height = h;
    printf("Width: %d, Height: %d\n", w, h);
}
