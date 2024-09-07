project "AudioPlayground"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/AudioPlayground/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/AudioPlayground/")
    
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

    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/AudioPlayground/"
    
    postbuildcommands {
        "{RMDIR} ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Snake/AudioPlayground/",
        "{COPYDIR} ../../Engine/Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/AudioPlayground/Assets/",
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/AudioPlayground/Assets/"
    }

    filter "configurations:Debug"
        includedirs {
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }