#ifndef CORE_H
#define CORE_H

#if !defined(SHR_PLATFORM_LINUX) && !defined(SHR_PLATFORM_WINDOWS)
	#define SHR_PLATFORM_LINUX
#endif

#ifdef SHR_PLATFORM_LINUX
	// #define SOKOL_GLCORE
#endif // DEBUG

#ifdef SHR_PATFORM_WINDOWS
	#include <Windows.h>
	#define SOKOL_D3D11
#endif // DEBUG

#define BIT(x) (1 << x)
#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#endif // !CORE_H
