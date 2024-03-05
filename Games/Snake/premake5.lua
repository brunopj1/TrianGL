project "Snake"
	kind "ConsoleApp"
	language "C++"

    targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

debugdir "."

    includedirs {
        "../../Engine/Source/",
        "../../Libs/glm/glm/",
        "Source/"
    }

    files {
        "premake5.lua",
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }

    links { "Engine" }