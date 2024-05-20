#ifndef SHR_LOG_H
#define SHR_LOG_H

#include "log.h"

#if defined(SHR_DEBUG)
	#define SHR_ERROR(...) log_error(__VA_ARGS__)
	#define SHR_WARN(...)  log_warn(__VA_ARGS__)
	#define SHR_INFO(...)  log_info(__VA_ARGS__)
	#define SHR_TRACE(...) log_trace(__VA_ARGS__)
	#define SHR_FATAL(...) log_fatal(__VA_ARGS__)

	#define SHR_ASSERT(condition, message) \
		if(!(condition)) { \
			SHR_ERROR((message)); \
			exit(-1); \
		}
#else
	#define SHR_ERROR(...) do {} while (0)
	#define SHR_WARN(...) do {} while (0)
	#define SHR_INFO(...) do {} while (0)
	#define SHR_TRACE(...) do {} while (0)
	#define SHR_FATAL(...) do {} while (0)
	#define SHR_ASSERT(condition, message) do {} while (0)
#endif

#endif // !SHR_LOG_H
