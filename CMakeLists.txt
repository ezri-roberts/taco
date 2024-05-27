#
# project: shraybn
#
cmake_minimum_required(VERSION 3.21)
project(shraybn)
# include the fips main cmake file
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

include_directories(
	include
	engine/src
	engine/lib/log
	engine/lib/sokol
	engine/lib/nuklear
	engine/lib/cglm/include
	/home/user/proj/c/fips-build/shraybn/linux-make-debug/engine
)

fips_setup()
add_subdirectory(engine/lib/rres)
add_subdirectory(engine/lib/log)
add_subdirectory(packer)
add_subdirectory(engine)
add_subdirectory(runtime)
# add_subdirectory(editor)
