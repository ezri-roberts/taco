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
include_dir["sokol"] = "taco/lib/sokol"

include "packer"
-- include "taco/lib/sokol"

project "taco"
	location "taco"
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
		"%{prj.name}/include",
		"%{prj.name}/src",
		"%{include_dir.packer}",
		"%{include_dir.sokol}",
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
			"packer",
		}

		defines
		{
			"LOG_USE_COLOR",		-- So the log library outputs color.
			"TC_PLATFORM_LINUX",
			"TC_BUILD_DYNAMIC",
		}

		postbuildcommands
		{
			-- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
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

project "sandbox"
	location "sandbox"
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
		"taco/src",
	}

	links
	{
		"taco"
	}

	filter "system:linux"

		links
		{
			"m", --"GL", "dl", "pthread", "X11", "Xi", "Xcursor", "rt", "Xrandr",
			-- "glfw3",
		}

		defines
		{
			"TC_PLATFORM_LINUX",
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

project "taco-shell"
	location "taco-shell"
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
		"taco/src",
	}

	links
	{
		"taco"
	}

	filter "system:linux"

		links
		{
			"m", --"GL", "dl", "pthread", "X11", "Xi", "Xcursor", "rt", "Xrandr",
			-- "glfw3",
		}

		defines
		{
			"TC_PLATFORM_LINUX",
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
