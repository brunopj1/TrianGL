project "Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
    objdir    ("../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs {
        "../Libs/glad/glad/include/",
        "../Libs/glfw/glfw/include/",
        "../Libs/glm/glm/",
        "Source/"
    }
    
    files {
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }

    links {
        "GLAD",
        "GLFW",
        "GLM"
    }

    defines {
        "IMGUI_DEFINE_MATH_OPERATORS"
    }

    filter "configurations:Debug"
        links {
            "ImGui",
            "ImGui-Stdlib"
        }
        includedirs {
            "../Libs/imgui/imgui/",
            "../Libs/imgui/imgui/backends/",
            "../Libs/imgui/imgui-stdlib/"
        }

    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }