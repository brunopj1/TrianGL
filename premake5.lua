workspace "TrianGL"
    startproject "Snake"
    
    cppdialect "C++20"

    configurations { "Debug", "Release", "Testing" }
    platforms { "Win32", "Win64" }

    systemversion "latest"
	staticruntime "On"
    
    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "Speed"
        defines { "NDEBUG" }
        flags { "LinkTimeOptimization" }

    filter "configurations:Testing"
        runtime "Debug" -- Debugging does not work in release mode
        symbols "On"
        defines { "DEBUG", "TESTING" }

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"

include "Engine/premake5.lua"

include "Tests/premake5.lua"

group "Dependencies"
    include "Libs//glad/premake5.lua"
    include "Libs/glfw/premake5.lua"
    include "Libs/glm/premake5.lua"
    include "Libs/imgui/premake5.lua"
    include "Libs/soloud/premake5.lua"
    include "Libs/stb_image/premake5.lua"
    include "Libs/googletest/premake5.lua"

group "Playground"
    include "Playground/AudioPlayground/premake5.lua"
    include "Playground/ParticlePlayground/premake5.lua"

group "Games"
    include "Games/Snake/premake5.lua"
