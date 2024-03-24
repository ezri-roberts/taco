#ifndef TCPCH_H
#define TCPCH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "taco/core.h"
#include "taco/log.h"

#define SOKOL_IMPL
#define SOKOL_GLES3
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"

#ifdef TC_PATFORM_WINDOWS
	#include <Windows.h>
#endif // DEBUG

#endif // !TCPCH_H
