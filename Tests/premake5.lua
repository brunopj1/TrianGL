project "Tests"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir("../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    
    includedirs {
        "../Engine/Source/",
        "../Libs/glm/glm/",
        "../Libs/googletest/googletest/googletest/include/",
        "Source/"
    }
    
    files {
        "premake5.lua",
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }
    
    links {
        "Engine",
        "Google-Test"
    }

    debugdir "../Bin/%{cfg.buildcfg}/%{cfg.platform}/"

    filter "configurations:not Testing"
        kind "None"