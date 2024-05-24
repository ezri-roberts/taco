#include "buffer.h"

void shrvertex_buffer_create(sg_range vertices, const char *label) {

	shrrenderer *renderer = shrenderer_get();

	renderer->bind.vertex_buffers[renderer->used_vbuffers] = sg_make_buffer(
		&(sg_buffer_desc){
			.data = vertices,
			.label = label
	});

	renderer->used_vbuffers++;
}
