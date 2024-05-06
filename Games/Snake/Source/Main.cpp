#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>
#include "Util/MemoryLeakDetection.h"

int main()
{
    TGL::ApplicationConfig config;
    config.WindowTitle = "TrianGL - Snake";
    config.Vsync = true;

    TGL::Application app{config};
    app.SetGameMode<SnakeGameMode>();

    app.Run();

    // Detect memory leaks (Will only run in Debug configurations)
    TGL::DetectMemoryLeaks();

    return 0;
}
