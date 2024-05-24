#ifndef BUFFER_H
#define BUFFER_H

#include "renderer.h"
#include "shrpch.h"

void shrvertex_buffer_create(sg_range vertices, const char *label);
void shrindex_buffer_create();

#endif // !BUFFER_H
