#ifndef IMAGE_H
#define IMAGE_H

#include "raylib.h"

typedef struct {

	Texture2D texture;

} Sprite;

Sprite *sprite_new(const char *path);

#endif // !IMAGE_H
