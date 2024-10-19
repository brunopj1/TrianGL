project "AudioPlayground"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/")
    
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

    defines {
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    links { "Engine" }

    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/"
    
    postbuildcommands {
        "{RMDIR} ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/Assets/",
        "{COPYDIR} ../../Engine/Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/Assets/",
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/Assets/"
    }

    filter "configurations:Debug"
        includedirs {
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }