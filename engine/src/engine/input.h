#ifndef INPUT_H
#define INPUT_H

#include "shrpch.h"
#include "input_codes.h"
#include "events/event.h"

typedef struct {

	uint16_t value;
	bool down;
	bool down_previous;
	bool pressed;
	bool released;
} shrinput;

typedef struct {

	// uint8_t key_down[KEYCODE_MAX / 8];
	shrinput inputs[INPUT_CODE_NUM];

} shrinput_state;

shrinput_state shrinput_state_new();
bool shrinput_state_handle_event(shrinput_state *state, const shrevent *event);
void shrinput_state_update(shrinput_state *state);
void shrinput_state_reset(shrinput_state *state);
bool _handle_key(shrinput_state *state, const shrevent *event);
bool _handle_mouse(shrinput_state *state, const shrevent *event);

bool input_down(uint16_t input_code);
bool input_pressed(uint16_t input_code);
bool input_released(uint16_t input_code);

#endif // !INPUT_H
