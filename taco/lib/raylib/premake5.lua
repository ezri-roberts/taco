project "raylib"
kind "StaticLib"
language "C"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("obj/" .. outputdir .. "/%{prj.name}")

includedirs {"src/", "src/external/glfw/include/" }

files
{
    "src/config.h",
    "src/raylib.h",
    "src/raymath.h",
    "src/rcamera.h",
    "src/rgestures.h",
    "src/rlgl.h",
    "src/utils.h",

    "src/raudio.c",
    "src/rcore.c",
    "src/rglfw.c",
    "src/rmodels.c",
    "src/rshapes.c",
    "src/rtext.c",
    "src/rtextures.c",
    "src/utils.c",
}

defines{"PLATFORM_DESKTOP"}
defines{"GRAPHICS_API_OPENGL_33"}
-- defines{"GRAPHICS_API_OPENGL_43"}
-- defines{"GRAPHICS_API_OPENGL_21"}
-- defines{"GRAPHICS_API_OPENGL_11"}

filter "system:linux"
    pic "On"
    systemversion "latest"
    staticruntime "On"

    defines {"_GNU_SOURCE"}

filter "system:windows"
    systemversion "latest"
    staticruntime "On"

filter "configurations:debug"
    runtime "Debug"
    symbols "On"

filter "configurations:release"
    runtime "Release"
    optimize "On"
