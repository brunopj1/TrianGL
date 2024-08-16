#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/MemoryLeakDetection.h"

i32 main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - Snake";
    config.Vsync = false;

    TGL::Application app{config};

    app.Run<SnakeGameMode>();

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();
}
