#include "input.h"

static shrinput_state state = {};
static bool initialized = false;

void shrinput_initialize() {
	memset(&state, 0, sizeof(shrinput_state));
	initialized = true;
	SHR_INFO("Input system initialized.");
}

void shrinput_shutdown() {
	// TODO: Potential shutdown routines.
	initialized = false;
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

// shrinput_state shrinput_state_new() {
//
// 	shrinput_state state;
// 	shrinput_state_reset(&state);
//
// 	return state;
// }
//
// void shrinput_state_reset(shrinput_state *state) {
// 	memset(state->inputs, 0, sizeof(state->inputs));
// 	TC_INFO("Input State Reset.");
// }
//
// bool shrinput_state_handle_event(shrinput_state *state, const shrevent *event) {
//
// 	if (shrevent_in_category(event, EVENT_CATEGORY_KEYBOARD)) {
// 		_handle_key(state, event);
// 		return true;
// 	} else if (shrevent_in_category(event, EVENT_CATEGORY_MOUSE_BUTTON)) {
// 		_handle_mouse(state, event);
// 		return true;
// 	}
//
// 	return false;
// }
//
// void shrinput_state_update(shrinput_state *state) {
//
// 	for (u8 i = 0; i < INPUT_CODE_NUM; i++) {
// 	
// 		u8 *input = &state->inputs[i];
//
// 		(INPUT_GET_BIT(input, BIT_DOWN) == 1) ?
// 			INPUT_SET_BIT(input, BIT_DOWN_PREV) :
// 			INPUT_UNSET_BIT(input, BIT_DOWN_PREV);
// 		(INPUT_GET_BIT(input, BIT_VALUE) > 0) ?
// 			INPUT_SET_BIT(input, BIT_DOWN) :
// 			INPUT_UNSET_BIT(input, BIT_DOWN);
// 		(INPUT_GET_BIT(input, BIT_DOWN) == 1 && INPUT_GET_BIT(input, BIT_DOWN_PREV) == 0) ? 
// 			INPUT_SET_BIT(input, BIT_PRESSED) :
// 			INPUT_UNSET_BIT(input, BIT_PRESSED);
// 		(INPUT_GET_BIT(input, BIT_DOWN_PREV) == 1 && INPUT_GET_BIT(input, BIT_DOWN) == 0) ? 
// 			INPUT_SET_BIT(input, BIT_RELEASED) :
// 			INPUT_UNSET_BIT(input, BIT_RELEASED);
// 	}
// }
//
// bool input_down(u16 input_code) {
//
// 	if (input_code > INPUT_CODE_NUM) {
// 		TC_ERROR("No Keycode '%d'");
// 		return false;
// 	}
//
// 	shrapp *app = (shrapp*)sapp_userdata();
//
// 	u8 *input = &app->input_state.inputs[input_code];
// 	return (bool) INPUT_GET_BIT(input, BIT_DOWN);
// }
//
// bool input_pressed(u16 input_code) {
//
// 	if (input_code > INPUT_CODE_NUM) {
// 		TC_ERROR("No Keycode '%d'");
// 		return false;
// 	}
//
// 	shrapp *app = (shrapp*)sapp_userdata();
//
// 	u8 *input = &app->input_state.inputs[input_code];
// 	return (bool) INPUT_GET_BIT(input, BIT_PRESSED);
// }
//
// bool input_released(u16 input_code) {
//
// 	if (input_code > INPUT_CODE_NUM) {
// 		TC_ERROR("No Keycode '%d'");
// 		return false;
// 	}
//
// 	shrapp *app = (shrapp*)sapp_userdata();
//
// 	u8 *input = &app->input_state.inputs[input_code];
// 	return (bool) INPUT_GET_BIT(input, BIT_RELEASED);
// }
//
// void _handle_key(shrinput_state *state, const shrevent *event) {
//
// 	u16 input_code = event->data.key_code;
// 	u8 *input = &state->inputs[input_code];
//
// 	if (event->type == KEY_PRESS) {
// 		INPUT_SET_BIT(input, BIT_VALUE);
// 	} else if (event->type == KEY_RELEASE) {
// 		INPUT_UNSET_BIT(input, BIT_VALUE);
// 	}
// }
//
// void _handle_mouse(shrinput_state *state, const shrevent *event) {
//
// 	u16 input_code = event->data.mouse_button;
// 	u8 *input = &state->inputs[input_code];
//
// 	if (event->type == MOUSE_PRESS) {
// 		INPUT_SET_BIT(input, BIT_VALUE);
// 	} else if (event->type == MOUSE_RELEASE) {
// 		INPUT_UNSET_BIT(input, BIT_VALUE);
// 	}
// }
