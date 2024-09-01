project "GLAD"
	kind "StaticLib"
	language "C"
		
	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs { "glad/include/" }

    files {
        "premake5.lua",
        "glad/include/glad/glad.h",
        "glad/src/glad.c"
    }
    
	filter "system:linux"
		pic "On"
		defines {
			"_GLAD_X11"
		}

	filter "system:windows"
		defines { 
			"_GLAD_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Testing"
		kind "None"