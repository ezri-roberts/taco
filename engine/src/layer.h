#ifndef LAYER_H
#define LAYER_H

#define LAYER_STACK_SIZE 128

#include "shrpch.h"
#include "event/event.h"

typedef void (*shrlayer_callback)(void*);

typedef struct shrlayer {

	const char *name;
	bool enabled;

	shrlayer_callback on_attach;
	shrlayer_callback on_detach;
	shrlayer_callback on_update;
	shrlayer_callback on_draw;

	shrevent_callback on_event;

} shrlayer;

typedef struct shrlayer_desc {
	shrlayer_callback on_attach;
	shrlayer_callback on_detach;
	shrlayer_callback on_update;
	shrlayer_callback on_draw;
} shrlayer_desc;

shrlayer* shrlayer_new(const char *name);

#endif // !LAYER_H
