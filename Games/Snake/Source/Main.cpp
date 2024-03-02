#include "Core/Application.h"
#include <SnakeGameMode.h>
#include "Util/DebugFeatures.hpp"

int main()
{
    // Scope to avoid false positives during memory leak detection
    {
        Engine::Core::Application app;
        app.SetGameMode<SnakeGameMode>();
        app.Run();
    }

    // Memory leaks (Will only run in Debug configurations)
    DEBUG_MEMORY_LEAKS();

    return 0;
}
