project "ImGui-Stdlib"
	kind "StaticLib"
	language "C++"

	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs { "../imgui/imgui/" }

	files {
        "premake5.lua",
		"imgui/imgui_stdlib.cpp",
		"imgui/imgui_stdlib.h"
	}
	
	links {
        "ImGui"
    }