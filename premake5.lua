workspace "taco"
	architecture "x64"
	cdialect "C99"

	configurations
	{
		"debug",
		"release",
		"dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include_dir = {}
include_dir["packer"] = "packer/src"
include_dir["sokol"] = "engine/lib/sokol"

include "packer"

project "engine"
	location "engine"
	kind "SharedLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{include_dir.packer}",
		"%{include_dir.sokol}",
	}

	links
	{
		"packer",
	}

	pchheader "tcpch.h"

	filter "system:linux"
		cdialect "C99"
		staticruntime "On"

		libdirs
		{
			"taco/lib/",
		}

		links
		{
    		"X11", "Xi", "Xcursor", "EGL", "GL", "dl", "pthread", "m"
		}

		defines
		{
			"LOG_USE_COLOR",		-- So the log library outputs color.
			"TC_PLATFORM_LINUX",
			"TC_BUILD_DYNAMIC",
		}

		postbuildcommands
		{
		}	

	filter "configurations:debug"
		defines "TC_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "TC_RELEASE"
		optimize "On"

	filter "configurations:dist"
		defines "TC_DIST"
		optimize "On"

project "runtime"
	location "runtime"
	kind "ConsoleApp"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{include_dir.packer}",
		"engine/src",
		"%{include_dir.sokol}",
	}

	links
	{
		"engine"
	}

	filter "system:linux"

		links
		{
    		"X11", "Xi", "Xcursor", "EGL", "GL", "dl", "pthread", "m"
		}

	filter "configurations:debug"
		symbols "On"

	filter "configurations:release"
		optimize "On"

	filter "configurations:dist"
		optimize "On"

project "editor"
	location "editor"
	kind "ConsoleApp"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{include_dir.packer}",
		"engine/src",
		"%{include_dir.sokol}",
	}

	links
	{
		"engine"
	}

	filter "system:linux"

		links
		{
			"X11", "Xi", "Xcursor", "EGL", "GL", "dl", "pthread", "m"
		}

	filter "configurations:debug"
		symbols "On"

	filter "configurations:release"
		optimize "On"

	filter "configurations:dist"
		optimize "On"
