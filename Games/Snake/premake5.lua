project "Snake"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/")
    objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/")
    
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
    
    debugdir "../../Bin/%{cfg.buildcfg}/%{cfg.platform}/"
    
    postbuildcommands {
        "{COPYDIR} Assets/ ../../Bin/%{cfg.buildcfg}/%{cfg.platform}/Assets/"
    }