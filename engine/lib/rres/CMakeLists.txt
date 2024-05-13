fips_begin_lib(rres)

fips_dir(src)
fips_files(rres.h)

fips_dir(src/external)
fips_files(
	qoi.h
	aes.c aes.h
	lz4.c lz4.h
	monocypher.c monocypher.h
)

fips_end_app()
