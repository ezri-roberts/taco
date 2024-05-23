#ifndef DBUI_H
#define DBUI_H

#include "shrpch.h"
#include "event/event.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "nuklear.h"

void shrnk_initialize();
void shrnk_update();
void shrnk_render();
bool shrnk_handle_event(const sapp_event *data);
void shrnk_shutdown();
struct nk_context* shrnk_new_frame();

#endif // !DBUI_H
