#ifndef RENDERER_H
#define RENDERER_H

#include "shrpch.h"
#include "camera.h"
#include "containers/darray.h"

typedef struct {

	// sg_pipeline    pipeline;
	// sg_bindings    bind;
	// sg_pass_action pass_action;

	u8 used_vbuffers;
	u8 used_ibuffers;

} shrrenderer;

typedef struct shrrenderer_vs_params {
	mat4 view_projection;
} shrrenderer_vs_params;

// typedef struct shrvbuffer {
// 	sg_buffer *buffer;
// 	sg_bindings *binding;
// } shrvbuffer;

// typedef struct shrshader {
// 	sg_shader shader;
// 	sg_pipeline *pipeline;
// } shrshader;

// typedef const sg_shader_desc* (*shrshader_desc)(sg_backend backend);

bool shrrenderer_initialize();
void shrrenderer_shutdown();
void shrrenderer_begin();
void shrrenderer_end();
// void shrrenderer_submit(shrshader *shader, shrvbuffer *vertex_buffer);
shrrenderer* shrenderer_get();

// shrshader shrrenderer_make_shader(shrshader_desc desc, i8 *attributes, i8 size);
// shrvbuffer shrrenderer_vb_create(usize size, sg_range vertices, const char *label);
// void shrrenderer_apply_vs_uniform(i32 index, const sg_range *data);
// void shrrenderer_apply_fs_uniform(i32 index, const sg_range *data);

#endif // !RENDERER_H
