#include "Core/Application.h"
#include <GameMode/FantasylandGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - Fantasyland";
	config.Vsync = false;

	TGL::Application::Run<FantasylandGameMode>(config);
}
