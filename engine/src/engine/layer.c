#include "layer.h"

Layer* layer_new(const char *name) {

	Layer *layer = malloc(sizeof(Layer));

	layer->name = name;
	layer->on_attach = NULL;
	layer->on_detach = NULL;
	layer->on_update = NULL;
	layer->on_event = NULL;
	layer->enabled = true;

	return layer;
}

LayerStack layer_stack_new() {

	LayerStack stack;

	stack.layers = malloc(LAYER_STACK_SIZE * sizeof(Layer));
	stack.used = 0;
	stack.size = LAYER_STACK_SIZE;

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

int layer_stack_size(LayerStack *stack) {
	return stack->used;
}

Layer* layer_stack_get(LayerStack *stack, int index) {
	return stack->layers[index];
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
	stack->used = 0;
	stack->size = 0;
}

