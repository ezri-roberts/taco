#ifndef SHADER_H
#define SHADER_H

#include "shrpch.h"

typedef const sg_shader_desc* (*shrshader_builder)(sg_backend backend);
typedef struct shrshader_des {
	shrshader_builder builder;
	sg_pipeline *pipeline;
	sg_vertex_attr_state attributes[16];
	const char *label;
} shrshader_desc;

void shrshader_bind(shrshader_desc desc);

#endif // !SHADER_H
