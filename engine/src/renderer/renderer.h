#ifndef RENDERER_H
#define RENDERER_H

#include "shrpch.h"

typedef struct {

	sg_pipeline    pip;
	sg_bindings    bind;
	sg_pass_action pass_action;

} shrrenderer;

void shrrenderer_init(shrrenderer *renderer);
void shrrenderer_frame(shrrenderer *renderer);

void _shrrenderer_sokol_init(shrrenderer *renderer);

#endif // !RENDERER_H
