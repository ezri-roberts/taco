#include "input.h"
#include "application.h"

shrinput_state shrinput_state_new() {

	shrinput_state state;
	shrinput_state_reset(&state);

	return state;
}

void shrinput_state_reset(shrinput_state *state) {
	memset(state->inputs, 0, sizeof(state->inputs));
	TC_INFO("Input State Reset.");
}

bool shrinput_state_handle_event(shrinput_state *state, const shrevent *event) {

	if (shrevent_in_category(event, EVENT_CATEGORY_KEYBOARD)) {
		_handle_key(state, event);
	} else if (shrevent_in_category(event, EVENT_CATEGORY_MOUSE_BUTTON)) {
		_handle_mouse(state, event);
	}

	return false;
}

void shrinput_state_update(shrinput_state *state) {

	for (u8 i = 0; i < INPUT_CODE_NUM; i++) {
	
		u8 *input = &state->inputs[i];

		(INPUT_GET_BIT(input, BIT_DOWN) == 1) ?
			INPUT_SET_BIT(input, BIT_DOWN_PREV) :
			INPUT_UNSET_BIT(input, BIT_DOWN_PREV);
		(INPUT_GET_BIT(input, BIT_VALUE) > 0) ?
			INPUT_SET_BIT(input, BIT_DOWN) :
			INPUT_UNSET_BIT(input, BIT_DOWN);
		(INPUT_GET_BIT(input, BIT_DOWN) == 1 && INPUT_GET_BIT(input, BIT_DOWN_PREV) == 0) ? 
			INPUT_SET_BIT(input, BIT_PRESSED) :
			INPUT_UNSET_BIT(input, BIT_PRESSED);
		(INPUT_GET_BIT(input, BIT_DOWN_PREV) == 1 && INPUT_GET_BIT(input, BIT_DOWN) == 0) ? 
			INPUT_SET_BIT(input, BIT_RELEASED) :
			INPUT_UNSET_BIT(input, BIT_RELEASED);
	}
}

bool input_down(u16 input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	shrapp *app = (shrapp*)sapp_userdata();

	u8 *input = &app->input_state.inputs[input_code];
	return (bool) INPUT_GET_BIT(input, BIT_DOWN);
}

bool input_pressed(u16 input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	shrapp *app = (shrapp*)sapp_userdata();

	u8 *input = &app->input_state.inputs[input_code];
	return (bool) INPUT_GET_BIT(input, BIT_PRESSED);
}

bool input_released(u16 input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	shrapp *app = (shrapp*)sapp_userdata();

	u8 *input = &app->input_state.inputs[input_code];
	return (bool) INPUT_GET_BIT(input, BIT_RELEASED);
}

void _handle_key(shrinput_state *state, const shrevent *event) {

	u16 input_code = event->data.key_code;
	u8 *input = &state->inputs[input_code];

	if (event->type == KEY_PRESS) {
		INPUT_SET_BIT(input, BIT_VALUE);
	} else if (event->type == KEY_RELEASE) {
		INPUT_UNSET_BIT(input, BIT_VALUE);
	}
}

void _handle_mouse(shrinput_state *state, const shrevent *event) {

	u16 input_code = event->data.mouse_button;
	u8 *input = &state->inputs[input_code];

	if (event->type == MOUSE_PRESS) {
		INPUT_SET_BIT(input, BIT_VALUE);
	} else if (event->type == MOUSE_RELEASE) {
		INPUT_UNSET_BIT(input, BIT_VALUE);
	}
}
