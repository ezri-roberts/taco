project("microui")
kind("StaticLib")
language("C")

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

includedirs({ "src/" })

files({
	"src/microui.h",
	"src/microui.c",
})

filter("system:linux")
pic("On")
systemversion("latest")
staticruntime("On")

filter("system:windows")
systemversion("latest")
staticruntime("On")

filter("configurations:debug")
runtime("Debug")
symbols("On")

filter("configurations:release")
runtime("Release")
optimize("On")
