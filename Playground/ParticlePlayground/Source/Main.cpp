#include "Core/Application.h"
#include <GameMode/ParticlePlaygroundGameMode.h>
#include "Util/MemoryLeakDetection.h"

i32 main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - ParticlePlayground";
    config.Vsync = false;

    TGL::Application::Run<ParticlePlaygroundGameMode>(config);

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}