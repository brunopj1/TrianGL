project "Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("../Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir    ("../Obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    includedirs {
        "../Libs/glad/glad/include/",
        "../Libs/glfw/glfw/include/",
        "../Libs/glm/glm/",
        "../Libs/imgui/imgui/",
        "../Libs/imgui/imgui/backends/",
        "../Libs/imgui/imgui-stdlib/",
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
        "GLM",
        "ImGui",
        "ImGui-Stdlib"
    }

    defines {
        "IMGUI_DEFINE_MATH_OPERATORS"
    }

    filter "system:linux"
        links { "dl", "pthread" }
        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }