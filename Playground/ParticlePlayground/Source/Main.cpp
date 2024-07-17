#include "Core/Application.h"
#include <GameMode/ParticlePlaygroundGameMode.h>
#include "Util/MemoryLeakDetection.h"

#ifndef DEBUG
static_assert(false, "The Playground projects are only available in Debug configurations");
#endif

i32 main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - ParticlePlayground";
    config.Vsync = false;

    TGL::Application app{config};
    app.SetGameMode<ParticlePlaygroundGameMode>();

    app.Run();

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}