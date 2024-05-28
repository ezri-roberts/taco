#include "renderer.h"

static shrrenderer renderer = {};
static bool initialized = false;

bool shrrenderer_initialize() {
	if (initialized) return false;

	initialized = false;

	memset(&renderer, 0, sizeof(shrrenderer));
	// memset(&renderer.pipeline, 0, sizeof(sg_pipeline));
	// memset(&renderer.bind, 0, sizeof(sg_bindings));

	renderer.used_vbuffers = 0;

	// sg_setup(&(sg_desc){
	// 	.environment = sglue_environment(),
	// 	.logger.func = slog_func,
	// });
	//
	// renderer.pass_action = (sg_pass_action) {
	// 	.colors[0] = {
	// 		.load_action = SG_LOADACTION_CLEAR,
	// 		.clear_value = {0.1f, 0.1f, 0.1f, 1.0f}
	// 	}
	// };

	if (!shrcamera_initialize(-1.6f, 1.6f, -0.9f, 0.9f)) {
		SHR_ERROR("Camera initialization failed.");
		return false;
	}

	initialized = true;

	const char *backend;
	#if defined(SOKOL_GLES3)
		backend = "GLES3";
	#elif defined(SOKOL_GLCORE)
		backend = "GLCORE";
	#elif defined(SOKOL_D3D11)
		backend = "D3D11";
	#endif

	SHR_INFO("[%s] Renderer initialized.", backend);
	return true;
}

void shrrenderer_shutdown() {
	if (!initialized) return;

	initialized = false;
}

void shrrenderer_begin() {

	// sg_begin_pass(&(sg_pass){.action = renderer.pass_action, .swapchain = sglue_swapchain()});
}

void shrrenderer_end() {

	// sg_end_pass();
	// sg_commit();
}

shrrenderer* shrenderer_get() {
	return &renderer;
}

// void shrrenderer_submit(shrshader *shader, shrvbuffer *vertex_buffer) {
// 	sg_apply_pipeline(*shader->pipeline);
// 	sg_apply_bindings(vertex_buffer->binding);
// 	sg_draw(0, 3, 1);
// }

// shrshader shrrenderer_make_shader(shrshader_desc desc, i8 *attributes, i8 size) {
//
// 	shrshader shader = {};
//
// 	shader.shader = sg_make_shader(desc(sg_query_backend()));
//
// 	sg_vertex_layout_state layout = {};
// 	memset(&layout, 0, sizeof(sg_vertex_layout_state));
//
// 	for (i8 i = 0; i < size; i++) {
// 		layout.attrs[i].format = attributes[i];	
// 	}
//
// 	renderer.pipeline = sg_make_pipeline(&(sg_pipeline_desc){
// 		.shader = shader.shader,
// 		// if the vertex layout doesn't have gaps, don't need to provide strides and offsets
// 		.layout = layout,
// 		.label = "triangle-pipeline"
// 	});
//
// 	shader.pipeline = &renderer.pipeline;
//
// 	return shader;
// }
//
// shrvbuffer shrrenderer_vb_create(usize size, sg_range vertices, const char *label) {
//
// 	shrvbuffer buffer = {};
//
// 	sg_buffer vb = sg_make_buffer(&(sg_buffer_desc){
//         .size = size,
//         .data = vertices,
//         .label = label
//     });
//
// 	renderer.bind.vertex_buffers[renderer.used_vbuffers] = vb;
// 	renderer.used_vbuffers++;
//
// 	buffer.buffer = &renderer.bind.vertex_buffers[renderer.used_vbuffers-1];
// 	buffer.binding = &renderer.bind;
//
// 	return buffer;
// }
//
// void shrrenderer_apply_vs_uniform(i32 index, const sg_range *data) {
// 	sg_apply_uniforms(SG_SHADERSTAGE_VS, index, data);
// }
