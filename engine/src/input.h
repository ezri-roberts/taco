#ifndef INPUT_H
#define INPUT_H

#include "shrpch.h"
#include "keycodes.h"
#include "event/event.h"

typedef enum shrinput_button {
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_MIDDLE,
	BUTTON_MAX
} shrinput_button;

typedef struct shrkeyboard_state {
	bool keys[256];
} shrkeyboard_state;

typedef struct shrmouse_state {
	vec2 position;
	u8 buttons[BUTTON_MAX];
} shrmouse_state;

typedef struct shrinput_state {
	shrkeyboard_state keyboard_current;
	shrkeyboard_state keyboard_previous;
	shrmouse_state mouse_current;
	shrmouse_state mouse_previous;
} shrinput_state;

bool shrinput_initialize();
void shrinput_shutdown();
void shrinput_update();
void shrinput_process_key(shrevent_data *data, bool pressed);
// void shrinput_process_button(const sapp_event *data, bool pressed);
// void shrinput_process_mouse_move(const sapp_event *data);
// void shrinput_process_mouse_wheel(const sapp_event *data);

// Keyboard Input.
bool input_key_down(shrinput_key key);
bool input_key_up(shrinput_key key);
bool input_key_pressed(shrinput_key key);
bool input_key_released(shrinput_key key);
bool input_key_was_down(shrinput_key key);
bool input_key_was_up(shrinput_key key);

// Mouse Input.
bool input_button_down(shrinput_button button);
bool input_button_up(shrinput_button button);
bool input_button_pressed(shrinput_button button);
bool input_button_released(shrinput_button button);
bool input_button_was_down(shrinput_button button);
bool input_button_was_up(shrinput_button button);
void shrinput_get_mouse_positon(vec2 position);
void shrinput_get_previous_mouse_positon(vec2 position);

#endif // !INPUT_H
