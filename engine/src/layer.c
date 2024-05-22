#include "layer.h"

shrlayer* shrlayer_new(const char *name) {

	shrlayer *layer = malloc(sizeof(shrlayer));

	layer->name = name;
	layer->on_attach = NULL;
	layer->on_detach = NULL;
	layer->on_update = NULL;
	layer->on_event = NULL;
	layer->enabled = true;

	return layer;
}

