workspace "taco"
	architecture "x64"

	configurations
	{
		"debug",
		"release",
		"dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/include"
	}

	filter "system:linux"
		cdialect "C99"
		staticruntime "On"

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
		"taco/src"
	}

	links
	{
		"taco"
	}

	filter "system:linux"
		cdialect "C99"
		staticruntime "On"

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
