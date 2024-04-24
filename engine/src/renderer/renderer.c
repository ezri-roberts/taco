#include "renderer.h"
#include "dbui/dbui.h"

void shrrenderer_init(shrrenderer *renderer) {

	shaderc_compiler_t shader_comp;

	sg_setup(&(sg_desc){
		.environment = sglue_environment(),
		.logger.func = slog_func,
	});

	sgl_setup(&(sgl_desc_t){
		.logger.func = slog_func,
	});

	float vertices[] = {
		// positions            // colors
		0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
	};

	renderer->bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
		.data = SG_RANGE(vertices),
		.label = "triangle-vertices"
	});

	renderer->pass_action = (sg_pass_action) {
		.colors[0] = {
			.load_action= SG_LOADACTION_CLEAR,
			.clear_value= {0.1f, 0.1f, 0.1f, 1.0f}
		}
	};

	const char *backend;
	#if defined(SOKOL_GLES3)
		backend = "GLES3";
	#elif defined(SOKOL_GLCORE33)
		backend = "GLCORE33";
	#elif defined(SOKOL_D3D11)
		backend = "D3D11";
	#endif

	TC_INFO("[%s] Renderer Initialized.", backend);
}

void shrrenderer_frame(shrrenderer *renderer) {

	sg_begin_pass(&(sg_pass){.action = renderer->pass_action, .swapchain = sglue_swapchain()});

	dbui_draw();

	sg_end_pass();
	sg_commit();
}
