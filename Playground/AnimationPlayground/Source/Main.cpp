#include "Core/Application.h"
#include "Core/MemoryLeakDetection.h"
#include <GameMode/AnimationPlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - AnimationPlayground";
	config.Vsync = false;

	TGL::Application::Run<AnimationPlaygroundGameMode>(config);

	// Detect memory leaks (Will only run in Debug configurations)
	TGL::DetectMemoryLeaks();
}
