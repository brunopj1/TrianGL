workspace "TrianGL"
    startproject "Snake"

    configurations { "Debug", "Release"}
    platforms { "Win32", "Win64" }

    filter "configurations:Debug*"
        runtime "Debug"
        symbols "On"
        defines { "DEBUG", "DEBUG_SHADER" }

    filter "configurations:Release*"
        runtime "Release"
        optimize "Speed"
        defines { "RELEASE" }
        flags { "LinkTimeOptimization" }

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"

    flags { "MultiProcessorCompile" }
    
    cppdialect "C++17"

include "Engine/premake5.lua"

group "Dependencies"
    include "Libs//glad/premake5.lua"
    include "Libs/glfw/premake5.lua"
    include "Libs/glm/premake5.lua"
    include "Libs/imgui/premake5.lua"
    include "Libs/imgui-stdlib/premake5.lua"

group "Games"
    include "Games/Snake/premake5.lua"