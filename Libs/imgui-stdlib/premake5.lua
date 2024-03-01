project "ImGui-Stdlib"
	kind "StaticLib"
	language "C++"

    targetdir ("../../Bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir    ("../../Obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    
    includedirs { "../imgui/imgui/" }

	files { 
		"imgui-stdlib/imgui_stdlib.cpp",
		"imgui-stdlib/imgui_stdlib.h"
	}
	
	links {
        "ImGui"
    }

	filter "configurations:Debug*"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		runtime "Release"
		optimize "on"