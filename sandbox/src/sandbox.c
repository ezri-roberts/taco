#include "taco.h"

struct nk_context *ctx;
App *app;

void test_layer_attach() {

	ctx = InitNuklear(10);
	TC_INFO("Layer attached.");
}

void test_layer_detach() {

	UnloadNuklear(ctx);
	TC_INFO("Layer detached.");
}

void test_layer_update(float delta_time) {

	UpdateNuklear(ctx);

	char fps[1010];
	sprintf(fps, "FPS: %d", app->fps);

	char scene[100];
	sprintf(scene, "Scene: %s", app->current_scene->name);

	if (nk_begin(ctx, "Debug", nk_rect(16, 16, 200, 100),
			  NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		nk_layout_row_dynamic(ctx, 12, 1);
		nk_label(ctx, fps, NK_TEXT_LEFT); 
		nk_label(ctx, scene, NK_TEXT_LEFT); 
	}
	nk_end(ctx);

	DrawNuklear(ctx);

	if (input_key_pressed(D)) {
		tc_app_set_scene(app, "scene2");
	}
}

App *tc_app_create() {

	app = tc_app_new();

	Layer *test_layer = layer_new("test");
	test_layer->on_attach = &test_layer_attach;
	test_layer->on_update = &test_layer_update;
	test_layer->on_detach = &test_layer_detach;
	
	Scene *default_scene = scene_new("default");
	scene_list_add(&app->scene_list, default_scene);
	Scene *scene_two = scene_new("scene2");
	scene_list_add(&app->scene_list, scene_two);

	layer_stack_push(&default_scene->layer_stack, test_layer);
	tc_app_set_scene(app, "default");
	
	return app;
}

