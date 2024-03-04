#ifndef LAYER_H
#define LAYER_H

#include <stdint.h>
#define MAX_LAYERS 100

#include "tcpch.h"

typedef struct {

	const char *name;
	bool enabled;

} Layer;

// typedef Layer LayerStack[MAX_LAYERS];
typedef struct {

	Layer *layers[MAX_LAYERS];
	uint16_t length;

} LayerStack;

Layer layer_new(const char *name);
void layer_update(Layer *layer);
LayerStack layer_stack_new();
void layer_stack_push(LayerStack *stack, Layer *layer);
void layer_stack_pop(LayerStack *stack, Layer *layer);

#endif // !LAYER_H
