project "ImGui-Stdlib"
	kind "StaticLib"
	language "C++"

	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs { "../imgui/imgui/" }

	files {
        "premake5.lua",
		"imgui-stdlib/imgui_stdlib.cpp",
		"imgui-stdlib/imgui_stdlib.h"
	}
	
	links {
        "ImGui"
    }