project "ImGui"
	kind "StaticLib"
	language "C++"
	
	targetdir ("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
	objdir    ("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

	includedirs {
		"imgui/",
		"imgui/backends/",
		"../glag/glad/include/",
		"../glfw/glfw/include/"
	}

	files {
		"imgui/*.cpp",
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_opengl3.cpp"
	}

	defines {
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}
    
	filter "system:linux"
		pic "On"
		defines {
			"_IMGUI_X11"
		}

	filter "system:windows"
		defines { 
			"_IMGUI_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}