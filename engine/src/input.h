#ifndef INPUT_H
#define INPUT_H

#include "shrpch.h"
#include "input_codes.h"
#include "event/event.h"

typedef struct {

	u16 value;
	bool down;
	bool down_previous;
	bool pressed;
	bool released;
} shrinput;

typedef struct {

	shrinput inputs[INPUT_CODE_NUM];

} shrinput_state;

shrinput_state shrinput_state_new();
bool shrinput_state_handle_event(shrinput_state *state, const shrevent *event);
void shrinput_state_update(shrinput_state *state);
void shrinput_state_reset(shrinput_state *state);
void _handle_key(shrinput_state *state, const shrevent *event);
void _handle_mouse(shrinput_state *state, const shrevent *event);

bool input_down(u16 input_code);
bool input_pressed(u16 input_code);
bool input_released(u16 input_code);

#endif // !INPUT_H
