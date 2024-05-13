#ifndef SHR_LOG_H
#define SHR_LOG_H

#include "log.h"

#if defined(SHR_DEBUG)
	#define TC_ERROR(...) log_error(__VA_ARGS__)
	#define TC_WARN(...)  log_warn(__VA_ARGS__)
	#define TC_INFO(...)  log_info(__VA_ARGS__)
	#define TC_TRACE(...) log_trace(__VA_ARGS__)
	#define TC_FATAL(...) log_fatal(__VA_ARGS__)

	#define TC_ASSERT(condition, message) \
		if(!(condition)) { \
			TC_ERROR((message)); \
			exit(-1); \
		}
#else
	#define TC_ERROR(...) do {} while (0)
	#define TC_WARN(...) do {} while (0)
	#define TC_INFO(...) do {} while (0)
	#define TC_TRACE(...) do {} while (0)
	#define TC_FATAL(...) do {} while (0)
	#define TC_ASSERT(condition, message) do {} while (0)
#endif

#endif // !SHR_LOG_H
