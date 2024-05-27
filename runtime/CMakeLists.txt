fips_begin_app(runtime windowed)

fips_dir(src)
fips_files(
	runtime.c
	ui_layer.c
)

fips_deps(engine)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_definitions(-DSHR_DEBUG)
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
	add_definitions(-DSHR_RELEASE)
endif()

fips_end_app()
