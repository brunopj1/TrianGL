project "AnimationPlayground"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/")
    
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
    
    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/"
    
    postbuildcommands {
        "{RMDIR} ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/Assets/",
        "{COPYDIR} ../../Engine/Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/Assets/",
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{projectName}/Assets/"
    }

    filter "configurations:Debug"
        includedirs {
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }