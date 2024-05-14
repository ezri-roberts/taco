fips_begin_lib(log_lib)

fips_files(
	log.c log.h
)

add_definitions(-DLOG_USE_COLOR)

fips_end_lib()
