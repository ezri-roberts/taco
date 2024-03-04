#include "layer.h"

Layer layer_new(const char *name) {

	Layer layer;

	layer.name = name;
	layer.enabled = true;

	return layer;
}

void layer_update(Layer *layer) {

}

LayerStack layer_stack_new() {

	LayerStack stack;
	stack.length = 0;

	return stack;
}

void layer_stack_push(LayerStack *stack, Layer *layer) {

	stack->layers[stack->length] = layer;
	stack->length++;

}

void layer_stack_pop(LayerStack *stack, Layer *layer) {

}
