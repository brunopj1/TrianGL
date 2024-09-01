project "Google-Test"
	kind "StaticLib"
	language "C++"

	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

    includedirs { 
		"googletest/googletest/include/",
		"googletest/googletest/"
	}

	files {
        "premake5.lua",
		"googletest/googletest/include/**.h",
		"googletest/googletest/src/*.cc"
	}

	filter "configurations:not Testing"
        kind "None"
