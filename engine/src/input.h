#ifndef INPUT_H
#define INPUT_H

#include "shrpch.h"
#include "keycodes.h"
#include "event/event.h"

#define BIT_VALUE     0
#define BIT_DOWN      1
#define BIT_DOWN_PREV 2
#define BIT_PRESSED   3
#define BIT_RELEASED  4

#define INPUT_GET_BIT(input, bit) (((*(input)) >> (bit)) & 1)
#define INPUT_SET_BIT(input, bit) (*(input) |= (1 << (bit)))
#define INPUT_UNSET_BIT(input, bit) (*(input) &= ~(1 << (bit)))
#define INPUT_RESET(input) (*(input) = (0x00))

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
	// i16 x; i16 y;
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
void shrinput_process_key(const sapp_event *data, bool pressed);
void shrinput_process_button(const sapp_event *data, bool pressed);
void shrinput_process_mouse_move(const sapp_event *data);
void shrinput_process_mouse_wheel(const sapp_event *data);

// Keyboard Input.
bool input_key_down(shrinput_key key);
bool input_key_up(shrinput_key key);
bool input_was_key_down(shrinput_key key);
bool input_was_key_up(shrinput_key key);

// Mouse Input.
bool input_button_down(shrinput_button button);
bool input_button_up(shrinput_button button);
bool input_was_button_down(shrinput_button button);
bool input_was_button_up(shrinput_button button);
void shrinput_get_mouse_positon(vec2 *position);
void shrinput_get_previous_mouse_positon(vec2 *position);

#endif // !INPUT_H
