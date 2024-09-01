#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/MemoryLeakDetection.h"

i32 main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - Snake";
    config.Vsync = false;

    TGL::Application::Run<SnakeGameMode>(config);

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}
