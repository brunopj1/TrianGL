#include "Core/Application.h"
#include <GameMode/AudioPlaygroundGameMode.h>
#include "Util/Macros/MemoryLeakMacros.h"

int main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - AudioPlayground";
    config.Vsync = true;

    TGL::Application app{config};
    app.SetGameMode<AudioPlaygroundGameMode>();

    app.Run();

    // Memory leaks (Will only run in Debug configurations)
    DEBUG_MEMORY_LEAKS();

    return 0;
}