#include "renderer.h"
#include "tri.glsl.h"

void shrrenderer_init(shrrenderer *renderer) {

	memset(&renderer->pip, 0, sizeof(sg_pipeline));
	memset(&renderer->bind, 0, sizeof(sg_bindings));

	sg_setup(&(sg_desc){
		.environment = sglue_environment(),
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

	sg_shader shd = sg_make_shader(triangle_shader_desc(sg_query_backend()));

	// create a pipeline object (default render states are fine for triangle)
	renderer->pip = sg_make_pipeline(&(sg_pipeline_desc){
		.shader = shd,
		// if the vertex layout doesn't have gaps, don't need to provide strides and offsets
		.layout = {
			.attrs = {
				[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3,
				[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4
			}
		},
		.label = "triangle-pipeline"
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
	#elif defined(SOKOL_GLCORE)
		backend = "GLCORE";
	#elif defined(SOKOL_D3D11)
		backend = "D3D11";
	#endif

	TC_INFO("[%s] Renderer Initialized.", backend);
}

void shrrenderer_begin(shrrenderer *renderer) {

	sg_begin_pass(&(sg_pass){.action = renderer->pass_action, .swapchain = sglue_swapchain()});
	sg_apply_pipeline(renderer->pip);
	sg_apply_bindings(&renderer->bind);
	sg_draw(0, 3, 1);
}

void shrrenderer_end() {
	sg_end_pass();
	sg_commit();
}

void shrrenderer_cleanup() {
}
