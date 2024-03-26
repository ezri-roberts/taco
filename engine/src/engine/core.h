#ifndef CORE_H
#define CORE_H

#if !defined(TC_PLATFORM_LINUX) && !defined(TC_PLATFORM_WINDOWS)
	#define TC_PLATFORM_LINUX
#endif

#define BIT(x) (1 << x)
#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

#endif // !CORE_H
