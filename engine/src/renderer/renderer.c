#include "renderer.h"

void shrrenderer_init(shrrenderer *renderer) {

    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });

	sgl_setup(&(sgl_desc_t){
        .logger.func = slog_func,
    });

	renderer->pass_action = (sg_pass_action) {
        .colors[0] = {
			.load_action= SG_LOADACTION_CLEAR,
			.clear_value= {0.0f, 0.0f, 0.0f, 1.0f}
		}
    };
}

void shrrenderer_frame(shrrenderer *renderer) {

    sg_begin_pass(&(sg_pass){.action = renderer->pass_action, .swapchain = sglue_swapchain()});

    sg_end_pass();
    sg_commit();
}
