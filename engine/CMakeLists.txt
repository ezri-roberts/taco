fips_begin_lib(engine)

fips_dir(src)
fips_files(
	core.h
	shrlog.h
	entrypoint.h
	input_codes.h
	input.c input.h
	layer.c layer.h
	scene.c scene.h
	window.c window.h
	application.c application.h
)

fips_dir(src/renderer)
fips_files(
	camera.c camera.h
	canvas.c canvas.h
	renderer.c renderer.h
	sprite.c sprite.h
)

fips_dir(src/event)
fips_files(event.c event.h)

fips_dir(src/dbui)
fips_files(dbui.c dbui.h)

fips_deps(log)
fips_deps(microui)
fips_deps(rres)

fips_libs(X11 Xi Xcursor EGL GL pthread m)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_definitions(-DSHR_DEBUG)
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
	add_definitions(-DSHR_RELEASE)
endif()

if (FIPS_LINUX)
	add_definitions(-DSHR_PLATFORM_LINUX)
elseif (FIPS_WINDOWS)
	add_definitions(-DSHR_PLATFORM_WINDOWS)
endif()

fips_end_sharedlib()
