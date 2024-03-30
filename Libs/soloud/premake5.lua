project "SoLoud"
	kind "StaticLib"
	language "C++"
		
	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

	includedirs { "soloud/include/" }

	files {
        "soloud/include/*.h",
		"soloud/src/core/*.h",
		"soloud/src/core/*.cpp",
		"soloud/src/audiosource/**.h",
		"soloud/src/audiosource/**.cpp",
		"soloud/src/audiosource/**.c",
		"soloud/src/backend/miniaudio/*.h",
		"soloud/src/backend/miniaudio/*.cpp"
	}

	defines { "WITH_MINIAUDIO" }

	filter "system:windows"
		defines { 
			"_CRT_SECURE_NO_WARNINGS"
		}