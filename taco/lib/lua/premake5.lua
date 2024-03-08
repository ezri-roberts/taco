project "lua"
kind "StaticLib"
language "C"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("obj/" .. outputdir .. "/%{prj.name}")

includedirs {"src/"}

files
{
	"src/lapi.h",
	"src/lauxlib.h",
	"src/lcode.h",
	"src/lctype.h",
	"src/ldebug.h",
	"src/ldo.h",
	"src/lfunc.h",
	"src/lgc.h",
	"src/ljumptab.h",
	"src/llex.h",
	"src/llimits.h",
	"src/lmem.h",

	"src/lauxlib.c",
	"src/lbaselib.c",
	"src/lcode.c",
	"src/lcorolib.c",
	"src/lctype.c",
	"src/ldblib.c",
	"src/ldebug.c",
	"src/ldo.c",
	"src/ldump.c",
	"src/lfunc.c",
	"src/lgc.c",
	"src/linit.c",
	"src/liolib.c",
	"src/llex.c",
	"src/lmathlib.c",
	"src/lmem.c",
	"src/loadlib.c",
	"src/lobject.c",
	"src/lopcodes.c",
	"src/loslib.c",
	"src/lparser.c",
	"src/lstate.c",
	"src/lstring.c",
	"src/lstrlib.c",
	"src/ltable.c",
	"src/ltablib.c",
	"src/ltm.c",
	"src/lua.c",
	"src/luac.c",
	"src/lundump.c",
	"src/lutf8lib.c",
	"src/lvm.c",
	"src/lzio.c",

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
