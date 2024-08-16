# Configuration ---------------------------------------------------------------

projectName = "ParticlePlayground"

isGame = False # If set to False, the project will be created in the 'Playgrounds' folder

# Includes --------------------------------------------------------------------

import os

# Templates -------------------------------------------------------------------

premakeTemplate = f"""
project "{projectName}"
    kind "ConsoleApp"
    language "C++"
    
    targetdir("../../Bin/%{{cfg.buildcfg}}/%{{cfg.platform}}/")
    objdir("../../Obj/%{{cfg.buildcfg}}/%{{cfg.platform}}/")
    
    includedirs {{
        "../../Engine/Source/",
        "../../Libs/glm/glm/",
        "Source/"
    }}
    
    files {{
        "premake5.lua",
        "Source/**.cpp",
        "Source/**.hpp",
        "Source/**.h"
    }}
    
    links {{ "Engine" }}
    
    debugdir "../../Bin/%{{cfg.buildcfg}}/%{{cfg.platform}}/"
    
    postbuildcommands {{
        "{{COPYDIR}} Assets/ ../../Bin/%{{cfg.buildcfg}}/%{{cfg.platform}}/Assets/"
    }}

    filter "configurations:Debug"
        includedirs {{
            "../../Libs/imgui/imgui/",
		    "../../Libs/imgui/imgui/misc/cpp/"
        }}
        defines {{
            "IMGUI_DEFINE_MATH_OPERATORS"
        }}
""".strip()

mainSourceStaticAssert = f"""
#ifndef DEBUG
static_assert(false, "The Playground projects are only available in Debug configurations");
#endif
"""

mainSourceTemplate = f"""
#include "Core/Application.h"
#include <GameMode/{projectName}GameMode.h>
#include "Util/MemoryLeakDetection.h"
{mainSourceStaticAssert if not isGame else ""}
i32 main()
{{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - {projectName}";
    config.Vsync = true;

    TGL::Application app{{config}};
    
    app.Run<{projectName}GameMode>();

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}}
""".strip()

gamemodeHeaderTemplate = f"""
#pragma once

#include "Game/GameMode.h"
#include "Core/DataTypes.h"

class {projectName}GameMode : public TGL::GameMode
{{
public:
    {projectName}GameMode();
    ~{projectName}GameMode() override = default;

private:
    void OnUpdate(f32 deltaTime) override;
    void OnEarlyUpdate(f32 deltaTime) override;
    void OnLateUpdate(f32 deltaTime) override;
}};
""".strip()

gamemodeSourceTemplate = f"""
#include "{projectName}GameMode.h"

#include "Implementations/Entities/Camera.h"

using namespace TGL;

{projectName}GameMode::{projectName}GameMode()
{{
    Camera* camera = SpawnEntity<Camera>(true);
}}

void {projectName}GameMode::OnUpdate(f32 deltaTime)
{{
    
}}

void {projectName}GameMode::OnEarlyUpdate(f32 deltaTime)
{{
    
}}

void {projectName}GameMode::OnLateUpdate(f32 deltaTime)
{{
    
}}
""".strip()

# Functions -------------------------------------------------------------------

def exitWithError(message : str):
    print(f"Failed to create the project")
    print(f"Error: {message}")
    exit()

# Run -------------------------------------------------------------------------

if not projectName.isidentifier():
    exitWithError(f"The project name is not a valid")

os.chdir(os.path.dirname(os.path.abspath(__file__)) + "/..")

newFolderPath = f"{"Games" if isGame else "Playground"}/{projectName}"

if os.path.exists(newFolderPath):
    exitWithError(f"The project folder already exists: {newFolderPath}")

os.makedirs(newFolderPath)
os.chdir(newFolderPath)

os.makedirs("Assets")
os.makedirs("Source")
os.makedirs("Source/GameMode")

with open("Source/Main.cpp", "w") as file:
    file.write(mainSourceTemplate)

with open("Source/GameMode/" + projectName + "GameMode.h", "w") as file:
    file.write(gamemodeHeaderTemplate)

with open("Source/GameMode/" + projectName + "GameMode.cpp", "w") as file:
    file.write(gamemodeSourceTemplate)

with open("premake5.lua", "w") as file:
    file.write(premakeTemplate)

premakeInclude = f'include "{newFolderPath}/premake5.lua"'
print(f"Project created successfully")
print(f"Add the following line to the main premake5.lua file: {premakeInclude}")