#include "scene.h"

shrscene* shrscene_new(const char *name) {

	shrscene *scene = malloc(sizeof(shrscene));

	scene->name = name;
	scene->on_attach = NULL;
	scene->on_detach = NULL;
	scene->on_update = NULL;
	scene->layer_stack = shrlayer_stack_new();

	return scene;
}

shrscene_list shrscene_list_new() {

	shrscene_list list;

	list.scenes = malloc(128 * sizeof(shrscene));
	list.used = 0;
	list.size = 128;

	return list;
}

void shrscene_list_add(shrscene_list *list, shrscene *scene) {

	TC_INFO("Added Scene: '0x%x'", scene);

	if (list->used == list->size) {
		list->size *= 2;
		list->scenes = realloc(list->scenes, list->size * sizeof(shrscene));
	}
	list->scenes[list->used++] = scene;
}

void shrscene_list_destroy(shrscene_list *list) {

	TC_INFO("Destroying Scene List: '0x%x'", list);

	for (usize i = 0; i < list->used; i++) {

		shrscene *scene = list->scenes[i];

		TC_INFO("Destroying Scene: '0x%x'", scene);
		shrlayer_stack_destory(&scene->layer_stack);
		free(scene);
		scene = NULL;
	}

	free(list->scenes);
	list->scenes = NULL;
	list->used = list->size = 0;
}
