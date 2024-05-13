#ifndef SCENE_H
#define SCENE_H

#include "shrpch.h"
#include "layer.h"

typedef struct {

	const char *name;
	shrlayer_stack layer_stack;

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)();

} shrscene;

typedef struct {

	shrscene **scenes;

	size_t used;
	size_t size;

} shrscene_list;

shrscene* shrscene_new(const char *name);
shrscene_list shrscene_list_new();
void shrscene_list_add(shrscene_list *list, shrscene *scene);
void shrscene_list_destroy(shrscene_list *list);

#endif // !SCENE_H
