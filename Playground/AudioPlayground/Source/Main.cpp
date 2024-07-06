#include "Core/Application.h"
#include <GameMode/AudioPlaygroundGameMode.h>
#include "Util/MemoryLeakDetection.h"

void main()
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
