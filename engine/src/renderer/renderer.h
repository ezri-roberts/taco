#ifndef RENDERER_H
#define RENDERER_H

#include "shrpch.h"

typedef struct {

	sg_pipeline    pip;
	sg_bindings    bind;
	sg_pass_action pass_action;

} shrrenderer;

bool shrrenderer_initialize();
void shrrenderer_begin();
void shrrenderer_end();
void shrrenderer_shutdown();

#endif // !RENDERER_H
