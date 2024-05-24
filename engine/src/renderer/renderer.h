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

bool shrrenderer_initialize();
void shrrenderer_begin();
void shrrenderer_end();
void shrrenderer_shutdown();
shrrenderer* shrenderer_get();

#endif // !RENDERER_H
