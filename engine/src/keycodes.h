#ifndef KEYCODES_H
#define KEYCODES_H

#include "shrpch.h"
#include <SDL2/SDL_keycode.h>

typedef enum shrinput_key {

	KEY_UNKNOWN             = 0,

	KEY_SPACE               = SDLK_SPACE,
	KEY_APOSTROPHE          = SDLK_QUOTE, /* ' */
	KEY_COMMA               = SDLK_COMMA, /* , */
	KEY_MINUS               = SDLK_MINUS, /* - */
	KEY_PERIOD              = SDLK_PERIOD, /* . */
	KEY_SLASH               = SDLK_SLASH, /* / */
	KEY_D0                  = SDLK_0, /* 0 */
	KEY_D1                  = SDLK_1, /* 1 */
	KEY_D2                  = SDLK_2, /* 2 */
	KEY_D3                  = SDLK_3, /* 3 */
	KEY_D4                  = SDLK_4, /* 4 */
	KEY_D5                  = SDLK_5, /* 5 */
	KEY_D6                  = SDLK_6, /* 6 */
	KEY_D7                  = SDLK_7, /* 7 */
	KEY_D8                  = SDLK_8, /* 8 */
	KEY_D9                  = SDLK_9, /* 9 */
	KEY_SEMICOLON           = SDLK_SEMICOLON, /* ; */
	KEY_EQUAL               = SDLK_EQUALS, /* = */
	KEY_A                   = SDLK_a,
	KEY_B                   = SDLK_b,
	KEY_C                   = SDLK_c,
	KEY_D                   = SDLK_d,
	KEY_E                   = SDLK_e,
	KEY_F                   = SDLK_f,
	KEY_g                   = SDLK_g,
	KEY_h                   = SDLK_h,
	KEY_i                   = SDLK_i,
	KEY_j                   = SDLK_j,
	KEY_k                   = SDLK_k,
	KEY_l                   = SDLK_l,
	KEY_m                   = SDLK_m,
	KEY_n                   = SDLK_n,
	KEY_o                   = SDLK_o,
	KEY_p                   = SDLK_p,
	KEY_q                   = SDLK_q,
	KEY_r                   = SDLK_r,
	KEY_s                   = SDLK_s,
	KEY_t                   = SDLK_t,
	KEY_u                   = SDLK_u,
	KEY_v                   = SDLK_v,
	KEY_w                   = SDLK_w,
	KEY_x                   = SDLK_x,
	KEY_y                   = SDLK_y,
	KEY_z                   = SDLK_z,
	KEY_LEFTBRACKET         = SDLK_LEFTBRACKET,  /* [ */
	KEY_BACKSLASH           = SDLK_BACKSLASH,  /* \ */
	KEY_RIGHTBRACKET        = SDLK_RIGHTBRACKET,  /* ] */
	// KEY_GRAVEACCENT         = SDLK_GRAVEACCENT,  /* ` */
	// KEY_WORLD1              = 161, /* NON-US #1 */
	// KEY_WORLD2              = 162, /* NON-US #2 */
	/* FUNCTION KEYS */
	KEY_ESCAPE              = SDLK_ESCAPE,
	KEY_ENTER               = SDLK_RETURN,
	KEY_TAB                 = SDLK_TAB,
	KEY_BACKSPACE           = SDLK_BACKSPACE,
	KEY_INSERT              = SDLK_INSERT,
	KEY_DELETE              = SDLK_DELETE,
	KEY_RIGHT               = SDLK_RIGHT,
	KEY_LEFT                = SDLK_LEFT,
	KEY_DOWN                = SDLK_DOWN,
	KEY_UP                  = SDLK_UP,
	KEY_PAGEUP              = SDLK_PAGEUP,
	KEY_PAGEDOWN            = SDLK_PAGEDOWN,
	KEY_HOME                = SDLK_HOME,
	KEY_END                 = SDLK_END,
	KEY_CAPSLOCK            = SDLK_CAPSLOCK,
	KEY_SCROLLLOCK          = SDLK_SCROLLLOCK,
	KEY_NUMLOCK             = SDLK_NUMLOCKCLEAR,
	KEY_PRINTSCREEN         = SDLK_PRINTSCREEN,
	KEY_PAUSE               = SDLK_PAUSE,
	KEY_F1                  = SDLK_F1,
	KEY_F2                  = SDLK_F2,
	KEY_F3                  = SDLK_F3,
	KEY_F4                  = SDLK_F4,
	KEY_F5                  = SDLK_F5,
	KEY_F6                  = SDLK_F6,
	KEY_F7                  = SDLK_F7,
	KEY_F8                  = SDLK_F8,
	KEY_F9                  = SDLK_F9,
	KEY_F10                 = SDLK_F10,
	KEY_F11                 = SDLK_F11,
	KEY_F12                 = SDLK_F12,
	KEY_F13                 = SDLK_F13,
	KEY_F14                 = SDLK_F14,
	KEY_F15                 = SDLK_F15,
	KEY_F16                 = SDLK_F16,
	KEY_F17                 = SDLK_F17,
	KEY_F18                 = SDLK_F18,
	KEY_F19                 = SDLK_F19,
	KEY_F20                 = SDLK_F20,
	KEY_F21                 = SDLK_F21,
	KEY_F22                 = SDLK_F22,
	KEY_F23                 = SDLK_F23,
	KEY_F24                 = SDLK_F24,
	/* KEYPAD */
	KEY_KP0                 = SDLK_KP_0,
	KEY_KP1                 = SDLK_KP_1,
	KEY_KP2                 = SDLK_KP_2,
	KEY_KP3                 = SDLK_KP_3,
	KEY_KP4                 = SDLK_KP_4,
	KEY_KP5                 = SDLK_KP_5,
	KEY_KP6                 = SDLK_KP_6,
	KEY_KP7                 = SDLK_KP_7,
	KEY_KP8                 = SDLK_KP_8,
	KEY_KP9                 = SDLK_KP_9,
	KEY_KPDECIMAL           = SDLK_KP_DECIMAL,
	KEY_KPDIVIDE            = SDLK_KP_DIVIDE,
	KEY_KPMULTIPLY          = SDLK_KP_MULTIPLY,
	KEY_KPSUBTRACT          = SDLK_KP_MINUS,
	KEY_KPADD               = SDLK_KP_PLUS,
	KEY_KPENTER             = SDLK_KP_ENTER,
	KEY_KPEQUAL             = SDLK_KP_EQUALS,
	KEY_LEFTSHIFT           = SDLK_LSHIFT,
	KEY_LEFTCONTROL         = SDLK_RSHIFT,
	KEY_LEFTALT             = SDLK_LALT,
	KEY_RIGHTSHIFT          = SDLK_RSHIFT,
	KEY_RIGHTCONTROL        = SDLK_RCTRL,
	KEY_RIGHTALT            = SDLK_LALT,
	KEY_MENU                = SDLK_MENU,

	KEYS_MAX
} shrinput_key;

#endif // !KEYCODES_H
