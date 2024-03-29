#ifndef LAYER_H
#define LAYER_H

#define LAYER_STACK_SIZE 128

#include "tcpch.h"
#include "events/event.h"

typedef struct {

	const char *name;
	bool enabled;

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)();

	EventCallback on_event;

} Layer;

typedef struct {

	Layer **layers;

	size_t used;
	size_t size;

} LayerStack;

Layer* layer_new(const char *name);
LayerStack layer_stack_new();
void layer_stack_destory(LayerStack *stack);
void layer_stack_push(LayerStack *stack, Layer *layer);
void layer_stack_pop(LayerStack *stack, Layer *layer);
Layer* layer_stack_get(LayerStack *stack, int index);
int layer_stack_size(LayerStack *stack);

#endif // !LAYER_H
