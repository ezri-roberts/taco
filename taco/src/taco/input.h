#ifndef INPUT_H
#define INPUT_H

#include "tcpch.h"
#include "keycodes.h"

bool input_key_pressed(int keycode);
bool input_key_released(int keycode);
bool input_key_down(int keycode);
bool input_key_up(int keycode);

#endif // !INPUT_H
