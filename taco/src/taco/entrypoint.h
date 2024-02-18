#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "taco/application.h"
#include "taco/log.h"

#if defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_WINDOWS)

extern App* app_create();

int main (int argc, char *argv[]) {

	TC_TRACE("Initializing Engine.");
	
	App *app = tc_app_create();
	tc_app_run(app);

	TC_TRACE("Terminating Engine.");
	tc_app_destroy(app);

	return 0;
}

#endif // !TC_PLATFORM_LINUX

#endif // !ENTRYPOINT_H
