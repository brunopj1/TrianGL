project "STB-Image"
kind "StaticLib"
language "C"

targetdir("../../Bin/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")
objdir("../../Obj/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}")

includedirs { "stb_image/" }

files {
    "premake5.lua",
    "stb_image/stb_image.h",
    "empty.c"
}