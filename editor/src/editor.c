#include "taco.h"

App *app;

App* app_init() {

	app = app_new();

	return app;
}

void app_frame() {

}

void app_cleanup() {

	app_destroy(app);
}
// struct nk_context *ctx;
// App *app;
//
// enum nk_collapse_states states;
// Font font;
//
// void test_layer_attach() {
//
// 	font = LoadFont("InterVariable.ttf");
// 	ctx = InitNuklearEx(font, 12);
// 	TC_INFO("Layer attached.");
// }
//
// void test_layer_detach() {
//
// 	UnloadNuklear(ctx);
// 	UnloadFont(font);
// 	TC_INFO("Layer detached.");
// }
//
// void test_layer_update(float delta_time) {
//
// 	UpdateNuklear(ctx);
//
// 	if (nk_begin(ctx, "Menu", nk_rect(0, 0, app->window.data.width, 30), NK_WINDOW_BORDER)) {
//
// 		nk_menubar_begin(ctx);
// 		nk_layout_row_static(ctx, 12, 40, 50);
//
// 		if (nk_menu_begin_label(ctx, "File", NK_TEXT_LEFT, nk_vec2(150, 200))) {
//
// 			nk_layout_row_dynamic(ctx, 25, 1);
// 			if (nk_menu_item_label(ctx, "New", NK_TEXT_LEFT)) {}
// 			if (nk_menu_item_label(ctx, "Open", NK_TEXT_LEFT)) {}
// 			if (nk_menu_item_label(ctx, "Save", NK_TEXT_LEFT)) {}
// 			if (nk_menu_item_label(ctx, "Quit", NK_TEXT_LEFT)) {
//
// 				tc_app_quit(app);
// 			}
//
// 			nk_menu_end(ctx);
// 		}
//
// 		nk_menubar_end(ctx);
// 	}
// 	nk_end(ctx);
//
// 	if (nk_begin(ctx, "Scene", nk_rect(0, 28, 256, app->window.data.height), NK_WINDOW_BORDER)) {
//
// 		nk_layout_row_dynamic(ctx, 10, 1);
//
// 		if (nk_tree_state_push(ctx, NK_TREE_NODE, "Scenes", &states)) {
//
// 			nk_label(ctx, "Scene1", NK_TEXT_LEFT);
// 			nk_label(ctx, "Scene2", NK_TEXT_LEFT);
// 			nk_label(ctx, "Scene3", NK_TEXT_LEFT);
// 			nk_tree_pop(ctx);
// 		}
// 	}
// 	nk_end(ctx);
//
// 	DrawNuklear(ctx);
// }
//
// App *tc_app_create() {
//
// 	app = tc_app_new();
//
// 	Layer *test_layer = layer_new("test");
// 	test_layer->on_attach = &test_layer_attach;
// 	test_layer->on_update = &test_layer_update;
// 	test_layer->on_detach = &test_layer_detach;
//
// 	Scene *editor_scene = scene_new("EditorScene");
// 	scene_list_add(&app->scene_list, editor_scene);
// 	layer_stack_push(&editor_scene->layer_stack, test_layer);
// 	tc_app_set_scene(app, "EditorScene");
// 	
// 	return app;
// }
//
