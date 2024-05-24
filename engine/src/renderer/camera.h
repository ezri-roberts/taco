#ifndef CAMERA_H
#define CAMERA_H

#include "shrpch.h"

typedef struct shrcamera {

	mat4 projection_matrix;
	mat4 view_matrix;
	mat4 view_projection_matrix;

	vec3 position;
	f32 rotation;
} shrcamera;

bool shrcamera_initialize(f32 left, f32 right, f32 bottom, f32 top);
void shrcamera_destroy();
void shrcamera_set_position(vec3 position);
void shrcamera_set_rotation(f32 rotation);
shrcamera* shrcamera_get();
void _recalculate_view_matrix();

#endif // !CAMERA_H
