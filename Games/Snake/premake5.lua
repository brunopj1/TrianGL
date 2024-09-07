project "Snake"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/Snake/")
    
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
    
    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/"
    
    postbuildcommands {
        "{RMDIR} ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/Assets/",
        "{COPYDIR} ../../Engine/Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/Assets/",
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/Assets/"
    }

    filter "configurations:Debug"
        includedirs {
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }