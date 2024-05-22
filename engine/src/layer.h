#ifndef LAYER_H
#define LAYER_H

#define LAYER_STACK_SIZE 128

#include "shrpch.h"
#include "event/event.h"

typedef struct shrlayer {

	const char *name;
	bool enabled;

	void (*on_attach)(void*);
	void (*on_detach)(void*);
	void (*on_update)(void*);

	shrevent_callback on_event;

} shrlayer;

typedef struct shrlayer_desc {
	void (*on_attach)(void*);
	void (*on_detach)(void*);
	void (*on_update)(void*);
} shrlayer_desc;

shrlayer* shrlayer_new(const char *name);

#endif // !LAYER_H
