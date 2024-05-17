#ifndef SHRPCH_H
#define SHRPCH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "core.h"

#ifdef SHR_PLATFORM_LINUX
	#define SOKOL_GLCORE
#endif // DEBUG

#ifdef SHR_PATFORM_WINDOWS
	#include <Windows.h>
	#define SOKOL_D3D11
#endif // DEBUG

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "nuklear.h"
// Quick hack to fix mismatch.
// sokol_gfx uses SG_BACKEND_GLCORE33
// sokol-shdc uses SG_BACKEND_GLCORE
// #define SG_BACKEND_GLCORE SG_BACKEND_GLCORE33

#include "shrlog.h"
#include "cglm/cglm.h"

#endif // !SHRPCH_H
