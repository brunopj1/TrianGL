#include "Core/Application.h"
#include <GameMode/AudioPlaygroundGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - AudioPlayground";
	config.Vsync = true;

	TGL::Application::Run<AudioPlaygroundGameMode>(config);
}
