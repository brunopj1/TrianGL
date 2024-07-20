project "Tests"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir("../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    
    includedirs {
        "../Engine/Source/",
        "../Libs/glad/glad/include/",
        "../Libs/glfw/glfw/include/",
        "../Libs/glm/glm/",
        "../Libs/soloud/soloud/include/",
        "../Libs/stb_image/stb_image/",
        "../Libs/googletest/googletest/googletest/include/"
    }
    
    files {
        "premake5.lua",
        "**.cpp"
    }
    
    links {
        "Engine",
        "Google-Test"
    }