#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/Macros/MemoryLeakMacros.hpp"

int main()
{
    // Scope to avoid false positives during memory leak detection
    {
        TGL::ApplicationConfig config;
        config.WindowTitle = "TrianGL - Snake";
        config.Vsync = true;

        TGL::Application app{config};
        app.SetGameMode<SnakeGameMode>();

        app.Run();
    }

    // Memory leaks (Will only run in Debug configurations)
    DEBUG_MEMORY_LEAKS();

    return 0;
}
