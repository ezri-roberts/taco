#include "layer.h"

Layer* layer_new(const char *name) {

	Layer *layer = malloc(sizeof(Layer));

	layer->name = name;
	layer->on_attach = NULL;
	layer->on_detach = NULL;
	layer->on_update = NULL;
	layer->enabled = true;

	return layer;
}

LayerStack layer_stack_new() {

	LayerStack stack;

	stack.layers = malloc(128 * sizeof(Layer));
	stack.used = 0;
	stack.size = 128;

	return stack;
}

void layer_stack_push(LayerStack *stack, Layer *layer) {

	if (layer->on_attach) layer->on_attach();

	if (stack->used == stack->size) {
		stack->size *= 2;
		stack->layers = realloc(stack->layers, stack->size * sizeof(Layer));
	}
	stack->layers[stack->used++] = layer;

}

void layer_stack_pop(LayerStack *stack, Layer *layer) {

}

void layer_stack_destory(LayerStack *stack) {

	TC_INFO("Destroying Layer Stack: '0x%x'", stack);

	for (int i = 0; i < stack->used; i++) {

		Layer *layer = stack->layers[i];
		if (layer->on_detach) layer->on_detach();

		TC_INFO("Destroying Layer: 0x%x", layer);
		free(layer);
		layer = NULL;
	}

	free(stack->layers);
	stack->layers = NULL;
	stack->used = stack->size = 0;
	
}

