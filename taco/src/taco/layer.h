#ifndef LAYER_H
#define LAYER_H

#define MAX_LAYERS 200
#define OVERLAY_INDEX_START 150

#include "tcpch.h"

typedef struct {

	const char *name;
	bool enabled;

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)(float delta_time);

} Layer;

typedef struct {

	Layer *layers[MAX_LAYERS];
	uint16_t layer_index;
	uint16_t overlay_index;

} LayerStack;

Layer* layer_new(const char *name);
LayerStack layer_stack_new();
void layer_stack_destory(LayerStack *stack);
void layer_stack_push(LayerStack *stack, Layer *layer);
void layer_stack_pop(LayerStack *stack, Layer *layer);
void layer_stack_push_overlay(LayerStack *stack, Layer *overlay);
void layer_stack_pop_overlay(LayerStack *stack, Layer *overlay);

#endif // !LAYER_H
