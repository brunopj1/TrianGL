#include "Core/Application.h"
#include "Core/MemoryLeakDetection.h"
#include <GameMode/AudioPlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - AudioPlayground";
	config.Vsync = true;

	TGL::Application::Run<AudioPlaygroundGameMode>(config);

	// Detect memory leaks (Will only run in Debug configurations)
	TGL::DetectMemoryLeaks();
}
