#include "Core/Application.h"
#include <GameMode/AudioPlaygroundGameMode.h>
#include "Util/MemoryLeakDetection.h"

#ifndef DEBUG
static_assert(false, "The Playground projects are only available in Debug configurations");
#endif

i32 main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - AudioPlayground";
    config.Vsync = true;

    TGL::Application app{config};
    app.SetGameMode<AudioPlaygroundGameMode>();

    app.Run();

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}
