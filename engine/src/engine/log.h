#ifndef TC_LOG_H
#define TC_LOG_H

#include "../log/log.h"

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


#endif // !TC_LOG_H
