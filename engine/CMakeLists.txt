fips_begin_lib(engine)

fips_dir(src)
fips_files(
	core.h
	shrlog.h
	engine.c engine.h
	entrypoint.h
	keycodes.h
	input.c input.h
	layer.c layer.h
	scene.c scene.h
	window.c window.h
	application.c application.h
)

fips_dir(src/containers)
fips_files(darray.c darray.h)

fips_dir(src/dbui)
fips_files(dbui.c dbui.h)

fips_dir(src/renderer)
fips_files(
	camera.c camera.h
	canvas.c canvas.h
	renderer.c renderer.h
	buffer.c buffer.h
	shader.c shader.h
	sprite.c sprite.h
)

fips_dir(src/event)
fips_files(event.c event.h)

fips_deps(log_lib)
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

# For shader comp.
if (FIPS_EMSCRIPTEN)
    # add_definitions(-DSOKOL_GLES3)
    set(slang "glsl300es")
elseif (FIPS_ANDROID)
    # add_definitions(-DSOKOL_GLES3)
    set(slang "glsl300es")
elseif (SOKOL_USE_D3D11)
    # add_definitions(-DSOKOL_D3D11)
    set(slang "hlsl5")
elseif (SOKOL_USE_METAL)
    # add_definitions(-DSOKOL_METAL)
    if (FIPS_IOS)
        set(slang "metal_ios:metal_sim")
    else()
        set(slang "metal_macos")
    endif()
else()
    if (FIPS_IOS)
        # add_definitions(-DSOKOL_GLES3)
        set(slang "glsl300es")
    else()
        # add_definitions(-DSOKOL_GLCORE)
        if (FIPS_MACOS)
            set(slang "glsl410")
        else()
            set(slang "glsl410")
        endif()
    endif()
endif()

fips_dir(src/renderer/shaders)
sokol_shader(tri.glsl ${slang})

fips_end_lib()
