#include "image.h"
#include "engine.h"

Sprite *sprite_new(const char *path) {

    engine.sprites[engine.sprites_len] = (Sprite) {
        .texture = LoadTexture(path)
    };
    engine.sprites_len ++;

    return &engine.sprites[engine.sprites_len - 1];
}
