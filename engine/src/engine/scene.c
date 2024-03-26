#include "scene.h"

Scene* scene_new(const char *name) {

	Scene *scene = malloc(sizeof(Scene));

	scene->name = name;
	scene->on_attach = NULL;
	scene->on_detach = NULL;
	scene->on_update = NULL;
	scene->layer_stack = layer_stack_new();

	return scene;
}

SceneList scene_list_new() {

	SceneList list;

	list.scenes = malloc(128 * sizeof(Scene));
	list.used = 0;
	list.size = 128;

	return list;
}

void scene_list_add(SceneList *list, Scene *scene) {

	TC_INFO("Added Scene: '0x%x'", scene);

	if (list->used == list->size) {
		list->size *= 2;
		list->scenes = realloc(list->scenes, list->size * sizeof(Scene));
	}
	list->scenes[list->used++] = scene;
}

void scene_list_destroy(SceneList *list) {

	TC_INFO("Destroying Scene List: '0x%x'", list);

	for (int i = 0; i < list->used; i++) {

		Scene *scene = list->scenes[i];

		TC_INFO("Destroying Scene: '0x%x'", scene);
		layer_stack_destory(&scene->layer_stack);
		free(scene);
		scene = NULL;
	}

	free(list->scenes);
	list->scenes = NULL;
	list->used = list->size = 0;
}
