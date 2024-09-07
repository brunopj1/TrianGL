project "Engine"
    kind "StaticLib"
    language "C++"
    
    targetdir("../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir("../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    
    includedirs {
        "../Libs/glm/glm/",
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
        "GLM",
        "STB-Image"
    }

    filter "configurations:not Testing"
        links {
            "GLAD",
            "GLFW",
            "SoLoud"
        }

        includedirs {
            "../Libs/glad/glad/include/",
            "../Libs/glfw/glfw/include/",
            "../Libs/soloud/soloud/include/"
        }
    
    filter "configurations:Debug"
        links {
            "ImGui"
        }
        
        includedirs {
            "../Libs/imgui/imgui/",
            "../Libs/imgui/imgui/backends/",
		    "../Libs/imgui/imgui/misc/cpp/"
        }
    
        defines {
            "IMGUI_DEFINE_MATH_OPERATORS"
        }
    
    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }
    
    filter "system:windows"
        defines { "_WINDOWS" }