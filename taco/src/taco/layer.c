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
	stack.layer_index = 0;
	stack.overlay_index = OVERLAY_INDEX_START;

	return stack;
}

void layer_stack_destory(LayerStack *stack) {

	TC_TRACE("Destroying layer stack.");
	uint16_t layer_amount = stack->layer_index;

	for (int i = 0; i <= layer_amount-1; i++) {

		Layer *layer = stack->layers[i];
		if (layer->on_detach) layer->on_detach();

		TC_TRACE("Destroying Layer: 0x%x", layer);
		free(layer);
		layer = NULL;
	}
	
}

void layer_stack_push(LayerStack *stack, Layer *layer) {

	if (layer->on_attach) layer->on_attach();
	stack->layers[stack->layer_index] = layer;
	stack->layer_index++;

}

void layer_stack_push_overlay(LayerStack *stack, Layer *overlay) {

	overlay->on_attach();
	stack->layers[stack->overlay_index] = overlay;
	stack->overlay_index++;
}

void layer_stack_pop(LayerStack *stack, Layer *layer) {

}

