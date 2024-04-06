#include "input.h"
#include "application.h"

InputState input_state_new() {

	InputState state;
	memset(state.controls, 0, sizeof(state.controls));

	return state;
}

bool input_state_handle_event(InputState *state, const Event *event) {

	uint16_t keycode = event->data.key_code;

	Control *control = &state->controls[keycode];
	control->value = 0;

	switch (event->type) {
	
		case KEY_PRESS:
			// control ^= 4;
			control->value = 1;
			return true;

		case KEY_RELEASE:
			control->value = 0;
			return true;

		default: return false;
	}
}

void input_state_update(InputState *state) {

	for (int i = 0; i < KEYCODES_NUM; i++) {
	
		Control *control = &state->controls[i];

		control->down_previous = control->down;
		control->down = control->value > 0;
		control->pressed = control->down && !control->down_previous;
		control->released = control->down_previous && !control->down;
	}

}

bool key_is_down(uint16_t keycode) {

	if (keycode > KEYCODES_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.controls[keycode].down;
}

bool key_is_pressed(uint16_t keycode) {

	if (keycode > KEYCODES_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.controls[keycode].pressed;
}

bool key_is_released(uint16_t keycode) {

	if (keycode > KEYCODES_NUM) {
		TC_ERROR("No Keycode '%d'");
		return false;
	}

	App *app = (App*)sapp_userdata();
	return app->input_state.controls[keycode].released;
}
