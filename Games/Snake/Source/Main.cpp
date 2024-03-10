#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/Macros/MemoryLeakMacros.hpp"

int main()
{
    // Scope to avoid false positives during memory leak detection
    {
        Engine::ApplicationConfig config;
        config.WindowTitle = "TrianGL - Snake";

        Engine::Application app{config};
        app.SetGameMode<SnakeGameMode>();

        app.Run();
    }

    // Memory leaks (Will only run in Debug configurations)
    DEBUG_MEMORY_LEAKS();

    return 0;
}
