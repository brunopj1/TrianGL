#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/DebugFeatures.hpp"

int main()
{
    // Scope to avoid false positives during memory leak detection
    {
        Engine::Core::ApplicationConfig config;
        config.Title = "TrianGL - Snake";

        Engine::Core::Application app{config};
        app.SetGameMode<SnakeGameMode>();

        app.Run();
    }

    // Memory leaks (Will only run in Debug configurations)
    DEBUG_MEMORY_LEAKS();

    return 0;
}
