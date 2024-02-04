#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef TC_PLATFORM_LINUX

extern App* app_create();

int main (int argc, char *argv[]) {

	TC_WARN("Initialized Log.");
	
	auto App *app = tc_app_create();
	tc_app_run(app);

	free(app);
	return 0;
}

#endif // !TC_PLATFORM_LINUX

#endif // !ENTRYPOINT_H
