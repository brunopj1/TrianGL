project "ParticlePlayground"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/")
    
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

    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/"
    
    postbuildcommands {
        "{RMDIR} ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/Assets/",
        "{COPYDIR} ../../Engine/Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/Assets/",
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/ParticlePlayground/Assets/"
    }

    filter "configurations:Debug"
        includedirs {
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }