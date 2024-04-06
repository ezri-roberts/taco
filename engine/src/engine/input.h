#ifndef INPUT_H
#define INPUT_H

#include "tcpch.h"
#include "keycodes.h"
#include "events/event.h"

#define KEYCODE_MAX 512
#define BIT_INDEX(key) ((key) / 8)
#define BIT_MASK(key) (1 << ((key) % 8))

typedef struct {

	uint16_t value;
	bool down;
	bool down_previous;
	bool pressed;
	bool released;
} Control;

typedef struct {

	// uint8_t key_down[KEYCODE_MAX / 8];
	Control controls[KEYCODES_NUM];

} InputState;

InputState input_state_new();
bool input_state_handle_event(InputState *state, const Event *event);
void input_state_update(InputState *state);

bool key_is_down(uint16_t keycode);
bool key_is_pressed(uint16_t keycode);
bool key_is_released(uint16_t keycode);

#endif // !INPUT_H
