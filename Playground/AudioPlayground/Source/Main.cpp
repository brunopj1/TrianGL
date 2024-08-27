#include "Core/Application.h"
#include "Util/MemoryLeakDetection.h"
#include <GameMode/AudioPlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - AudioPlayground";
	config.Vsync = true;

	TGL::Application app { config };

	app.Run<AudioPlaygroundGameMode>();

	// Detect memory leaks (Will only run in Debug configurations)
	TGL::DetectMemoryLeaks();
}
