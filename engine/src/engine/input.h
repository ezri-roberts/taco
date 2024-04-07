#ifndef INPUT_H
#define INPUT_H

#include "tcpch.h"
#include "input_codes.h"
#include "events/event.h"

typedef struct {

	uint16_t value;
	bool down;
	bool down_previous;
	bool pressed;
	bool released;
} Input;

typedef struct {

	// uint8_t key_down[KEYCODE_MAX / 8];
	Input inputs[INPUT_CODE_NUM];

} InputState;

InputState input_state_new();
bool input_state_handle_event(InputState *state, const Event *event);
bool _handle_key(InputState *state, const Event *event);
bool _handle_mouse(InputState *state, const Event *event);
void input_state_update(InputState *state);
void input_state_reset(InputState *state);

bool input_down(uint16_t keycode);
bool input_pressed(uint16_t keycode);
bool input_released(uint16_t keycode);

#endif // !INPUT_H
