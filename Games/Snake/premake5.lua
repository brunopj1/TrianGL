project "Snake"
	kind "ConsoleApp"
	language "C++"

    targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs {
        "../../Engine/Source/",
        "../../Libs/glm/glm/",
        "Source/"
    }

    files {
        -- C++ files
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }

    links { "Engine" }