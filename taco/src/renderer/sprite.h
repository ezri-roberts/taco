#ifndef SPRITE_H
#define SPRITE_H

#include "tcpch.h"

typedef struct {

	Texture2D texture;
	BlendMode blend_mode;
	Color color;

} Sprite;

Sprite sprite_new();

#endif // !SPRITE_H
