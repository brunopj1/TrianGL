project "GLM"
	kind "StaticLib"
	language "C++"

	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs { "glm/" }

	files {
		"glm/glm/**.cpp",
		"glm/glm/**.hpp",
		"glm/glm/**.h"
	}
    
	filter "system:linux"
		pic "On"
		defines {
			"_GLM_X11"
		}

	filter "system:windows"
		defines { 
			"_GLM_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}