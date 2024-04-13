#ifndef LAYER_H
#define LAYER_H

#define LAYER_STACK_SIZE 128

#include "shrpch.h"
#include "events/event.h"

typedef struct {

	const char *name;
	bool enabled;

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)();

	shrevent_callback on_event;

} shrlayer;

typedef struct {

	shrlayer **layers;

	size_t used;
	size_t size;

} shrlayer_stack;

shrlayer* shrlayer_new(const char *name);
shrlayer_stack shrlayer_stack_new();
void shrlayer_stack_destory(shrlayer_stack *stack);
void shrlayer_stack_push(shrlayer_stack *stack, shrlayer *layer);
void shrlayer_stack_push_front(shrlayer_stack *stack, shrlayer *layer);
void shrlayer_stack_pop(shrlayer_stack *stack, shrlayer *layer);
shrlayer* shrlayer_stack_get(shrlayer_stack *stack, int index);
int shrlayer_stack_size(shrlayer_stack *stack);

#endif // !LAYER_H
