#include "dbui.h"

#define SOKOL_NUKLEAR_IMPL
#include "sokol_nuklear.h"

void dbui_init() {

	snk_setup(&(snk_desc_t){
        .dpi_scale = sapp_dpi_scale(),
        .logger.func = slog_func,
    });
}

void dbui_update() {

	struct nk_context *ctx = snk_new_frame();

	if (nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),
			  NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		/* fixed widget pixel width */
		nk_layout_row_static(ctx, 30, 80, 1);
		if (nk_button_label(ctx, "button")) {
			/* event handling */
		}

		/* fixed widget window ratio width */
		nk_layout_row_dynamic(ctx, 30, 2);
		// if (nk_option_label(&ctx, "easy", op == EASY)) op = EASY;
		// if (nk_option_label(&ctx, "hard", op == HARD)) op = HARD;

		/* custom widget pixel width */
		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
		{
			nk_layout_row_push(ctx, 50);
			nk_label(ctx, "Volume:", NK_TEXT_LEFT);
			nk_layout_row_push(ctx, 110);
		}
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
}

bool dbui_event(shrevent *event) {
	bool handled = snk_handle_event(&event->data);
	return handled;
}

void dbui_render() {
	snk_render(sapp_width(), sapp_height());
}

void dbui_cleanup() {
	snk_shutdown();
}
