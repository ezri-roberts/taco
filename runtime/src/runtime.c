#include "shrentry.h"
#include "runtime.h"

#include "tri.glsl.h"

static shrvbuffer vbuffer;
static shrshader shader;

static shrcamera *cam; 
static vec3 cam_pos;

void tri_layer_attach(void *data) {

	cam = shrcamera_get();

	f32 vertices[] = {
		// positions            // colors
		0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
	};

	vbuffer = shrrenderer_vb_create(
		sizeof(vertices),
		SG_RANGE(vertices),
		"triangle-vertices"
	);

	i8 attr[] = {
		[ATTR_vs_position] = SG_VERTEXFORMAT_FLOAT3,
		[ATTR_vs_color0]   = SG_VERTEXFORMAT_FLOAT4
	};

	shader = shrrenderer_make_shader(triangle_shader_desc, attr, 2);
}

void tri_layer_draw(void *data) {
	shrrenderer_submit(&shader, &vbuffer);
}

void camera_layer_draw(void *data) {

	// shrcamera *cam = shrcamera_get();
	//
	// shrrenderer_vs_params params = {};
	// glm_mat4_copy(cam->view_projection_matrix, params.view_projection);
	//
	// shrrenderer_apply_vs_uniform(SLOT_vs_params, &SG_RANGE(params));
}

void shrapp_start() {

	shrapp_layer_new("tri_layer", (shrlayer_desc) {
		.on_attach = tri_layer_attach,
		.on_draw = tri_layer_draw 
	});
	// This layer applies the camera transform to all layers below it.
	shrapp_layer_new("camera_layer", (shrlayer_desc) {
		.on_draw = camera_layer_draw 
	});
	shrapp_layer_new("dbui_layer", (shrlayer_desc) {
		.on_attach = dbui_layer_attach,
		.on_detach = dbui_layer_detach,
		.on_update = dbui_layer_update,
		.on_draw = dbui_layer_draw
	});

	shrevent_register_category(EVENT_CATEGORY_MOUSE, 0, dbui_layer_event);
	shrevent_register_category(EVENT_CATEGORY_KEYBOARD, 0, dbui_layer_event);
}

void shrapp_update() {

	if (input_key_down(KEY_W)) {
		cam_pos[1] += 0.05;
	}
	if (input_key_down(KEY_A)) {
		cam_pos[0] -= 0.05;
	}
	if (input_key_down(KEY_S)) {
		cam_pos[1] -= 0.05;
	}
	if (input_key_down(KEY_D)) {
		cam_pos[0] += 0.05;
	}


	// Only update camera if needed.
	if (!glm_vec3_eqv(cam_pos, cam->position)) {
		shrcamera_set_position(cam_pos);
	}
}

void shrapp_draw() {

}

void shrapp_cleanup() {

	shrevent_unregister_category(EVENT_CATEGORY_MOUSE, 0, dbui_layer_event);
	shrevent_unregister_category(EVENT_CATEGORY_KEYBOARD, 0, dbui_layer_event);

	shrapp_shutdown();
}
