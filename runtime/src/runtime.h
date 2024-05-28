#ifndef RUNTIME_H
#define RUNTIME_H

#include "shraybn.h"

// UI Layer.
void dbui_layer_attach(void *data);
void dbui_layer_detach(void *data);
void dbui_layer_update(void *data);
void dbui_layer_draw(void *data);
// bool dbui_layer_event(u16 code, void *sender, void *listener, const sapp_event *data);

// Triangle Layer.
void tri_layer_attach(void *data);
void tri_layer_draw(void *data);

// Camera Layer.
void camera_layer_draw(void *data);

#endif // !RUNTIME_H
