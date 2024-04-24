workspace("shraybn")
architecture("x64")
cdialect("C99")

configurations({
	"debug",
	"release",
	"dist",
})

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include_dir = {}
include_dir["shaderc"] = "engine/lib/shaderc/libshaderc/include"
include_dir["packer"] = "packer/src"
include_dir["sokol"] = "engine/lib/sokol"
include_dir["microui"] = "engine/lib/microui/src"
include_dir["cglm"] = "engine/lib/cglm/include"

include("packer")
include("engine/lib/microui")

externalproject("shaderc")
configmap({
	["degug"] = "Debug",
	["release"] = "Release",
})
location("engine/lib/shaderc/build")
kind("StaticLib")
language("C++")

project("engine")
location("engine")
kind("SharedLib")
language("C")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("obj/" .. outputdir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.c",
})

includedirs({
	"%{prj.name}/src",
	"%{include_dir.shaderc}",
	"%{include_dir.packer}",
	"%{include_dir.sokol}",
	"%{include_dir.microui}",
	"%{include_dir.cglm}",
})

links({
	"microui",
	"packer",
})

pchheader("shrpch.h")

filter("system:linux")
cdialect("C99")
staticruntime("On")

libdirs({
	"engine/lib/",
	"engine/lib/shaderc/build/libshaderc/",
})

links({
	"X11",
	"Xi",
	"Xcursor",
	"EGL",
	"GL",
	"dl",
	"pthread",
	"m",
	"shaderc_combined",
})

defines({
	"LOG_USE_COLOR", -- So the log library outputs color.
	"SHR_PLATFORM_LINUX",
	"SHR_BUILD_DYNAMIC",
})

postbuildcommands({})

filter("configurations:debug")
defines("SHR_DEBUG")
symbols("On")

filter("configurations:release")
defines("SHR_RELEASE")
optimize("On")

filter("configurations:dist")
defines("SHR_DIST")
optimize("On")

project("runtime")
location("runtime")
kind("ConsoleApp")
language("C")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("obj/" .. outputdir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.c",
})

includedirs({
	"%{include_dir.shaderc}",
	"%{include_dir.packer}",
	"%{include_dir.sokol}",
	"%{include_dir.microui}",
	"%{include_dir.cglm}",
	"engine/src",
})

links({
	"engine",
})

filter("system:linux")

links({
	"X11",
	"Xi",
	"Xcursor",
	"EGL",
	"GL",
	"dl",
	"pthread",
	"m",
})

filter("configurations:debug")
defines("SHR_DEBUG")
symbols("On")

filter("configurations:release")
defines("SHR_RELEASE")
optimize("On")

filter("configurations:dist")
defines("SHR_DIST")
optimize("On")

project("editor")
location("editor")
kind("ConsoleApp")
language("C")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("obj/" .. outputdir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.c",
})

includedirs({
	"%{include_dir.shaderc}",
	"%{include_dir.include}",
	"%{include_dir.sokol}",
	"%{include_dir.microui}",
	"%{include_dir.cglm}",
	"engine/src",
})

links({
	"engine",
})

filter("system:linux")

links({
	"X11",
	"Xi",
	"Xcursor",
	"EGL",
	"GL",
	"dl",
	"pthread",
	"m",
})

filter("configurations:debug")
defines("SHR_DEBUG")
symbols("On")

filter("configurations:release")
defines("SHR_RELEASE")
optimize("On")

filter("configurations:dist")
defines("SHR_DIST")
optimize("On")
