#ifndef DBUI_H
#define DBUI_H

#include "shrpch.h"
#include "event/event.h"

void dbui_init();
void dbui_update();
void dbui_render();
bool dbui_event(const sapp_event *data);
void dbui_cleanup();

#endif // !DBUI_H
