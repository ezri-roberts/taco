#include "layer.h"

shrlayer* shrlayer_new(const char *name) {

	shrlayer *layer = malloc(sizeof(shrlayer));

	layer->name = name;
	layer->on_attach = NULL;
	layer->on_detach = NULL;
	layer->on_update = NULL;
	layer->on_event = NULL;
	layer->enabled = true;

	return layer;
}

shrlayer_stack shrlayer_stack_new() {

	shrlayer_stack stack;

	stack.layers = malloc(LAYER_STACK_SIZE * sizeof(shrlayer));
	stack.used = 0;
	stack.size = LAYER_STACK_SIZE;

	return stack;
}

void shrlayer_stack_push(shrlayer_stack *stack, shrlayer *layer) {

	if (layer->on_attach) layer->on_attach();

	if (stack->used == stack->size) {
		stack->size *= 2;
		stack->layers = realloc(stack->layers, stack->size * sizeof(shrlayer));
	}
	stack->layers[stack->used++] = layer;

}

void shrlayer_stack_pop(shrlayer_stack *stack, shrlayer *layer) {

}

int shrlayer_stack_size(shrlayer_stack *stack) {
	return stack->used;
}

shrlayer* shrlayer_stack_get(shrlayer_stack *stack, int index) {
	return stack->layers[index];
}

void shrlayer_stack_destory(shrlayer_stack *stack) {

	TC_INFO("Destroying Layer Stack: '0x%x'", stack);

	for (int i = 0; i < stack->used; i++) {

		shrlayer *layer = stack->layers[i];
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

