#ifndef SCENE_H
#define SCENE_H

#include "tcpch.h"
#include "taco/layer.h"

typedef struct {

	const char *name;
	LayerStack layer_stack;

	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)();

} Scene;

typedef struct {

	Scene **scenes;

	size_t used;
	size_t size;

} SceneList;

Scene* scene_new(const char *name);
SceneList scene_list_new();
void scene_list_add(SceneList *list, Scene *scene);
void scene_list_destroy(SceneList *list);

#endif // !SCENE_H
