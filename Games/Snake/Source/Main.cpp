#include "Core/Application.h"
#include <GameMode/SnakeGameMode.h>

i32 main()
{
	TGL::ApplicationConfig config;
	config.WindowTitle = "TrianGL - Snake";
	config.Vsync = false;

	TGL::Application::Run<SnakeGameMode>(config);
}
