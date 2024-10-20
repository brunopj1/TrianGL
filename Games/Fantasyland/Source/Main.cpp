#include "Core/Application.h"
#include "Core/MemoryLeakDetection.h"
#include <GameMode/FantasylandGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - Fantasyland";
	config.Vsync = false;

	TGL::Application::Run<FantasylandGameMode>(config);

	// Detect memory leaks (Will only run in Debug configurations)
	TGL::DetectMemoryLeaks();
}
