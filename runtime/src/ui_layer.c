#include "runtime.h"
#include "shrnuklear.h"

void dbui_layer_attach(void *data) {

	(void)data;

	shrnk_initialize();
	SHR_TRACE("[DBUI] Layer attached.");
}

void dbui_layer_detach(void *data) {
	SHR_TRACE("[DBUI] Layer detached.");
	shrnk_shutdown();
}

void dbui_layer_update(void *data) {

	(void)data;

	shrwindow_data win_data;
	shrwindow_get_data(&win_data);

	char win_size_tex[128];
	char mouse_pos_text[128];

	vec2 mouse_pos;
	shrinput_get_mouse_positon(mouse_pos);

	sprintf(win_size_tex, "Window Size: %ix%i", win_data.width, win_data.height);
	sprintf(mouse_pos_text, "Mouse Position: %.2f, %.2f", mouse_pos[0], mouse_pos[1]);

	struct nk_context *ctx = shrnk_new_frame();

	if (nk_begin(ctx, "Debug Info", nk_rect(50, 50, 256, 128),
			  NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		/* fixed widget pixel width */
		nk_layout_row_dynamic(ctx, 16, 1);

		nk_label(ctx, win_size_tex, NK_TEXT_LEFT);
		nk_label(ctx, mouse_pos_text, NK_TEXT_LEFT);
	}

	nk_end(ctx);
}

void dbui_layer_draw(void *data) {
	shrnk_render();
}

bool dbui_layer_event(u16 code, void *sender, void *listener, const sapp_event *data) {
	return shrnk_handle_event(data);
}
