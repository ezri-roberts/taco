#ifndef RENDERER_H
#define RENDERER_H

#include "shrpch.h"

typedef struct {

	sg_pipeline    pip;
	sg_bindings    bind;
	sg_pass_action pass_action;

	u8 used_vbuffers;
	u8 used_ibuffers;

} shrrenderer;

typedef struct shrrenderer_vs_params {
	mat4 view_projection;
} shrrenderer_vs_params;

typedef const sg_shader_desc* (*shrshader_desc)(sg_backend backend);

bool shrrenderer_initialize();
void shrrenderer_shutdown();
void shrrenderer_begin();
void shrrenderer_end();
void shrenderer_submit();
shrrenderer* shrenderer_get();

void shrrenderer_make_shader(const sg_shader_desc *desc, sg_vertex_attr_state attributes[16], i8 length);
void shrrenderer_vb_create(sg_range vertices, const char *label);
void shrrenderer_apply_vs_uniform(i32 index, const sg_range *data);
void shrrenderer_apply_fs_uniform(i32 index, const sg_range *data);

#endif // !RENDERER_H
