project "Snake"
	kind "ConsoleApp"
	language "C++"

    targetdir ("../../Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir    ("../../Obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

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