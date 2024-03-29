project "packer"
kind "StaticLib"
language "C"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("obj/" .. outputdir .. "/%{prj.name}")

includedirs {"src/"}

files
{
	"lib/rres/src/external/aes.h",
	"lib/rres/src/external/qoi.h",
	"lib/rres/src/external/lz4.h",
	"lib/rres/src/external/monocypher.h",
	"lib/rres/src/rres.h",
	"lib/rres/src/external/aes.c",
	"lib/rres/src/external/lz4.c",
	"lib/rres/src/external/monocypher.c",
    "src/packer.h",
    "src/packer.c",
}

filter "system:linux"
    pic "On"
    systemversion "latest"
    staticruntime "On"

filter "system:windows"
    systemversion "latest"
    staticruntime "On"

filter "configurations:debug"
    runtime "Debug"
    symbols "On"

filter "configurations:release"
    runtime "Release"
    optimize "On"
