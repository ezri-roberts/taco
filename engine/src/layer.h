#ifndef LAYER_H
#define LAYER_H

#define LAYER_STACK_SIZE 128

#include "shrpch.h"
#include "event/event.h"

typedef struct {

	const char *name;
	bool enabled;

	void (*on_attach)(void*);
	void (*on_detach)(void*);
	void (*on_update)(void*);

	shrevent_callback on_event;

} shrlayer;

typedef struct {

	shrlayer **layers;

	usize used;
	usize size;

} shrlayer_stack;

shrlayer* shrlayer_new(const char *name);
shrlayer_stack shrlayer_stack_new();
void shrlayer_stack_destory(shrlayer_stack *stack);
void shrlayer_stack_push(shrlayer_stack *stack, shrlayer *layer);
void shrlayer_stack_push_front(shrlayer_stack *stack, shrlayer *layer);
void shrlayer_stack_pop(shrlayer_stack *stack, shrlayer *layer);
shrlayer* shrlayer_stack_get(shrlayer_stack *stack, usize index);
int shrlayer_stack_size(shrlayer_stack *stack);

#endif // !LAYER_H
