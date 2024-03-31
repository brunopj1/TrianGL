project "Engine"
    kind "StaticLib"
    language "C++"
    
    targetdir("../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir("../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    
    includedirs {
        "../Libs/glad/glad/include/",
        "../Libs/glfw/glfw/include/",
        "../Libs/glm/glm/",
        "../Libs/soloud/soloud/include/",
        "../Libs/stb_image/stb_image/",
        "Source/"
    }
    
    files {
        "premake5.lua",
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }
    
    links {
        "GLAD",
        "GLFW",
        "GLM",
        "SoLoud",
        "STB-Image"
    }
    
    filter "configurations:Debug"
        links {
            "ImGui",
            "ImGui-Stdlib"
        }
        includedirs {
            "../Libs/imgui/imgui/",
            "../Libs/imgui/imgui/backends/",
            "../Libs/imgui_stdlib/imgui/"
        }
    
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }
    
    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }
    
    filter "system:windows"
        defines { "_WINDOWS" }
        
        postbuildcommands {
            "{RMDIR} ../Bin/%{cfg.buildcfg}/%{cfg.platform}/Assets/",
            "{COPYDIR} Assets/ ../Bin/%{cfg.buildcfg}/%{cfg.platform}/Assets/"
        }