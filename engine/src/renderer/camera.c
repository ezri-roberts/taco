#include "camera.h"

static shrcamera camera = {};
static bool initialized = false;

bool shrcamera_initialize(f32 left, f32 right, f32 bottom, f32 top) {
	if (initialized) return false;

	initialized = false;
	memset(&camera, 0, sizeof(shrcamera));

	glm_ortho(left, right, bottom, top, -1.0f, 1.0f, camera.projection_matrix);

	glm_mat4_copy(
		(mat4){
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
		camera.view_matrix
	);

	glm_mat4_mul(camera.projection_matrix, camera.view_matrix, camera.view_projection_matrix);

	glm_vec3_zero(camera.position);
	camera.rotation = 0.0f;

	initialized = true;

	SHR_INFO("Camera initialized.");
	return true;
}

void shrcamera_destroy() {
	if (!initialized) return;

	// TODO: Potential shutdown routines.
	initialized = false;
}

void shrcamera_set_position(vec3 position) {

	glm_vec3_copy(position, camera.position);
	_recalculate_view_matrix();
}

void shrcamera_set_rotation(f32 rotation) {

	camera.rotation = rotation;
	_recalculate_view_matrix();
}

void _recalculate_view_matrix() {

	mat4 trans = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};
	mat4 rot = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};
	mat4 transform;

	glm_translate(trans, camera.position);
	glm_rotate(rot, glm_rad(camera.rotation), (vec3){0.0f,0.0f,1.0f});
	glm_mat4_mul(trans, rot, transform);

	glm_mat4_inv(transform, camera.view_matrix);
	glm_mat4_mul(camera.projection_matrix, camera.view_matrix, camera.view_projection_matrix);
}

shrcamera* shrcamera_get() {
	return &camera;
}
