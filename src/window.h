#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

typedef struct {

	GLFWwindow *target;
	uint16_t	width;
	uint16_t	height;
	char	   *title;
} Window;

void window_init(Window *window, uint16_t width, uint16_t height, char *title);
bool window_should_close(Window *window);

#endif // !WINDOW_H
