#include "renderer.h"
#include "camera.h"
#include "tri.glsl.h"

static shrrenderer renderer = {};
static bool initialized = false;

bool shrrenderer_initialize() {
	if (initialized) return false;

	initialized = false;
	memset(&renderer, 0, sizeof(shrrenderer));
	memset(&renderer.pip, 0, sizeof(sg_pipeline));
	memset(&renderer.bind, 0, sizeof(sg_bindings));

	renderer.used_vbuffers = 0;

	sg_setup(&(sg_desc){
		.environment = sglue_environment(),
		.logger.func = slog_func,
	});

	f32 vertices[] = {
		// positions            // colors
		0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
	};

	shrrenderer_vb_create(SG_RANGE(vertices), "triangle-vertices");

	sg_vertex_attr_state attr[] = {
		[ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3,
		[ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4
	};
	shrrenderer_make_shader(triangle_shader_desc(sg_query_backend()), attr, 2);

	renderer.pass_action = (sg_pass_action) {
		.colors[0] = {
			.load_action = SG_LOADACTION_CLEAR,
			.clear_value = {0.1f, 0.1f, 0.1f, 1.0f}
		}
	};

	if (!shrcamera_initialize(-1.6f, 1.6f, -0.9f, 0.9f)) {
		SHR_ERROR("Camera initialization failed.");
		return false;
	}

	shrcamera_set_rotation(25.0f);

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

	// TODO: Potential shutdown routines.
	initialized = false;
}

void shrrenderer_begin() {

	sg_begin_pass(&(sg_pass){.action = renderer.pass_action, .swapchain = sglue_swapchain()});
	sg_apply_pipeline(renderer.pip);
	sg_apply_bindings(&renderer.bind);

	shrrenderer_vs_params params = {};
	memset(&params, 0, sizeof(shrrenderer_vs_params));

	shrcamera *cam = shrcamera_get();
	glm_mat4_copy(cam->view_projection_matrix, params.view_projection);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &SG_RANGE(params));
	sg_draw(0, 3, 1);

}

void shrrenderer_end() {

	sg_end_pass();
	sg_commit();
}

shrrenderer* shrenderer_get() {
	return &renderer;
}

void shrrenderer_make_shader(const sg_shader_desc *desc, sg_vertex_attr_state attributes[16], i8 length) {

	sg_shader shd = sg_make_shader(desc);

	sg_vertex_layout_state layout = {};
	memset(&layout, 0, sizeof(sg_vertex_layout_state));

	for (i8 i = 0; i < length; i++) {
		layout.attrs[i] = attributes[i];	
	}

	renderer.pip = sg_make_pipeline(&(sg_pipeline_desc){
		.shader = shd,
		// if the vertex layout doesn't have gaps, don't need to provide strides and offsets
		.layout = layout,
		.label = "triangle-pipeline"
	});
}

void shrrenderer_vb_create(sg_range vertices, const char *label) {

	renderer.bind.vertex_buffers[renderer.used_vbuffers] = sg_make_buffer(&(sg_buffer_desc){
		.data = vertices,
		.label = label
	});

	renderer.used_vbuffers++;
}

void shrrenderer_apply_vs_uniform(i32 index, const sg_range *data) {
	sg_apply_uniforms(SG_SHADERSTAGE_VS, index, data);
}
