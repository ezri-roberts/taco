#ifndef SHRPCH_H
#define SHRPCH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "engine/core.h"

#ifdef SHR_PLATFORM_LINUX
	#define SOKOL_GLCORE33
#endif // DEBUG

#ifdef SHR_PATFORM_WINDOWS
	#include <Windows.h>
	#define SOKOL_D3D11
#endif // DEBUG

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"
#include "sokol_gl.h"

#include "engine/log.h"
#include "cglm/cglm.h"

#endif // !SHRPCH_H
