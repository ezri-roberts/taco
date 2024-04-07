#include "input.h"
#include "application.h"

InputState input_state_new() {

	InputState state;
	input_state_reset(&state);

	return state;
}

void input_state_reset(InputState *state) {
	memset(state->inputs, 0, sizeof(state->inputs));
	TC_INFO("Input State Reset.");
}

bool input_state_handle_event(InputState *state, const Event *event) {

	if (event_in_category(event, EVENT_CATEGORY_KEYBOARD)) {
		return _handle_key(state, event);
	} else if (event_in_category(event, EVENT_CATEGORY_MOUSE_BUTTON)) {
		return _handle_mouse(state, event);
	}

	return false;
}

void input_state_update(InputState *state) {

	for (int i = 0; i < INPUT_CODE_NUM; i++) {
	
		Input *input = &state->inputs[i];

		input->down_previous = input->down;
		input->down = input->value > 0;
		input->pressed = input->down && !input->down_previous;
		input->released = input->down_previous && !input->down;
	}
}

bool input_down(uint16_t input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.inputs[input_code].down;
}

bool input_pressed(uint16_t input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.inputs[input_code].pressed;
}

bool input_released(uint16_t input_code) {

	if (input_code > INPUT_CODE_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.inputs[input_code].released;
}

bool _handle_key(InputState *state, const Event *event) {

	uint16_t input_code = event->data.key_code;
	Input *input = &state->inputs[input_code];

	if (event->type == KEY_PRESS) {
		input->value = 1;
		return true;
	} else if (event->type == KEY_RELEASE) {
		input->value = 0;
		return true;
	}

	return false;
}

bool _handle_mouse(InputState *state, const Event *event) {

	uint16_t input_code = event->data.mouse_button;
	Input *input = &state->inputs[input_code];

	if (event->type == MOUSE_PRESS) {
		input->value = 1;
		return true;
	} else if (event->type == MOUSE_RELEASE) {
		input->value = 0;
		return true;
	}

	return false;
}
