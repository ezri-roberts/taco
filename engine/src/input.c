#include "input.h"
#include "cglm/types.h"

static shrinput_state state = {};
static bool initialized = false;

bool shrinput_initialize() {
	if (initialized) return false;

	initialized = false;
	memset(&state, 0, sizeof(shrinput_state));

	initialized = true;

	SHR_INFO("Input system initialized.");
	return true;
}

void shrinput_shutdown() {
	// TODO: Potential shutdown routines.
	initialized = false;
	SHR_INFO("Input system shutdown.");
}

void shrinput_update() {
	if (!initialized) return;

	// Copy the current states to the previous states.
	memcpy(&state.keyboard_previous, &state.keyboard_current, sizeof(shrkeyboard_state));
	memcpy(&state.mouse_previous, &state.mouse_current, sizeof(shrmouse_state));
}

void shrinput_process_key(const sapp_event *data, bool pressed) {

	shrinput_key key = (shrinput_key)data->key_code;

	if (state.keyboard_current.keys[key] != pressed) {

		state.keyboard_current.keys[key] = pressed;
		shrevent_fire(pressed ? EVENT_KEY_PRESS : EVENT_KEY_RELEASE, 0, data);
	}
}

void shrinput_process_button(const sapp_event *data, bool pressed) {

	shrinput_button button = (shrinput_button)data->mouse_button;

	// if (state.mouse_current.buttons[button] != pressed) {

		state.keyboard_current.keys[button] = pressed;
		shrevent_fire(pressed ? EVENT_MOUSE_PRESS : EVENT_MOUSE_RELEASE, 0, data);
	// }
}

void shrinput_process_mouse_move(const sapp_event *data) {

	const i16 x = data->mouse_x;
	const i16 y = data->mouse_y;

	vec2 *pos = &state.mouse_current.position;

	if (*pos[0] != x || *pos[1] != y) {

		// SHR_TRACE("Mouse pos: %i, %i", x, y);

		*pos[0] = x;
		*pos[1] = y;
		shrevent_fire(EVENT_MOUSE_MOVE, 0, data);
	}
}

void shrinput_process_mouse_wheel(const sapp_event *data) {
	shrevent_fire(EVENT_MOUSE_SCROLL, 0, data);
}

// Keyboard Input.
bool input_key_down(shrinput_key key) {
	if(!initialized) return false;
	return state.keyboard_current.keys[key] == true;
}

bool input_key_up(shrinput_key key) {
	if(!initialized) return true;
	return state.keyboard_current.keys[key] == false;
}

bool input_key_was_down(shrinput_key key) {
	if(!initialized) return false;
	return state.keyboard_previous.keys[key] == true;
}

bool input_key_was_up(shrinput_key key) {
	if(!initialized) return true;
	return state.keyboard_previous.keys[key] == false;
}

// Mouse Input.
bool input_button_down(shrinput_button button) {
	if(!initialized) return false;
	return state.mouse_current.buttons[button] == true;
}

bool input_button_up(shrinput_button button) {
	if(!initialized) return true;
	return state.mouse_current.buttons[button] == false;
}

bool input_was_button_down(shrinput_button button) {
	if(!initialized) return false;
	return state.mouse_previous.buttons[button] == true;
}

bool input_was_button_up(shrinput_button button) {
	if(!initialized) return true;
	return state.mouse_previous.buttons[button] == false;
}

void shrinput_get_mouse_positon(vec2 *position) {
	if (!initialized) {
		*position[0] = 0;
		*position[1] = 0;
		return;	
	}

	*position[0] = state.mouse_current.position[0];
	*position[1] = state.mouse_current.position[1];
}

void shrinput_get_previous_mouse_positon(vec2 *position) {
	if (!initialized) {
		*position[0] = 0;
		*position[1] = 0;
		return;	
	}

	*position[0] = state.mouse_current.position[0];
	*position[1] = state.mouse_current.position[1];
}
