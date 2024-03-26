#ifndef TCPCH_H
#define TCPCH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "engine/core.h"

#ifdef TC_PLATFORM_LINUX
	#define SOKOL_GLES3
#endif // DEBUG

#ifdef TC_PATFORM_WINDOWS
	#include <Windows.h>
	#define SOKOL_D3D11
#endif // DEBUG

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"

#include "engine/log.h"

#endif // !TCPCH_H
