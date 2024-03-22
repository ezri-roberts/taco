#include "canvas.h"

Canvas canvas_new(int width, int height) {

	Canvas canvas;

	canvas.on_update = NULL;
	canvas.target = LoadRenderTexture(width, height);
	SetTextureFilter(canvas.target.texture, TEXTURE_FILTER_POINT);

	TC_TRACE("Created Canvas.");

	return canvas;
}

void canvas_update(Canvas *canvas) {


	BeginTextureMode(canvas->target);
	ClearBackground(WHITE);

	if (canvas->on_update) canvas->on_update();

	EndTextureMode();
}

void canvas_draw(Canvas *canvas, WindowData *win_data) {

	int width = canvas->target.texture.width;
	int height = canvas->target.texture.height;
	float scale = MIN((float)win_data->width/width, (float)win_data->height/height);

	canvas->source.x = 0;
	canvas->source.y = 0;
	canvas->source.width = (float)canvas->target.texture.width;
	canvas->source.height = (float) -canvas->target.texture.height;

	canvas->dest.x = (win_data->width - ((float)width * scale)) * 0.5f;
	canvas->dest.y = (win_data->height - ((float)height * scale)) * 0.5f;
	canvas->dest.width = (float)width * scale;
	canvas->dest.height = (float)height * scale;

	ClearBackground(BLACK);

	DrawTexturePro(
		canvas->target.texture, canvas->source, canvas->dest,
		(Vector2){0, 0}, 0.0f, WHITE
	);

}
